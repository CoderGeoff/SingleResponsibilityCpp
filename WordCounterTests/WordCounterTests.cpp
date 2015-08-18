#include "stdafx.h"
#include <memory>

#include <gtest/gtest.h>
#include "TemporaryDirectory.h"
#include <WordCounter.h>
#include "TemporaryFile.h"

TEST(WordCounterTests, GivenAnEmptyDirectory_WhenWordsAreCounted_ShouldBeZero)
{
    TemporaryDirectory directory;
    WordCounter counter(directory.Name());
    ASSERT_EQ(0, counter.WordCount());
}

TEST(WordCounterTests, GivenAnEmptyDirectory_WhenLongestWordIsQueried_LengthShouldBeZero)
{
    TemporaryDirectory directory;
    WordCounter counter(directory.Name());
    ASSERT_EQ(0, counter.LengthOfLongestWord());
}

TEST(WordCounterTests, GivenAnEmptyDirectory_WhenWordFrequencyIsQueried_ShouldBeZero)
{
    TemporaryDirectory directory;
    WordCounter counter(directory.Name());
    ASSERT_EQ(0, counter.Frequency("the"));
}

TEST(WordCounterTests, GivenOneFileWith5Words_WhenWordsAreCounted_ShouldBe5)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one two three four five");
    WordCounter counter(directory.Name());
    ASSERT_EQ(5, counter.WordCount());
}

TEST(WordCounterTests, GivenOneFileWith10LetterWordWords_WhenLongestWordIsQueried_ShouldBe10)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one two vegetarian three four five");
    WordCounter counter(directory.Name());
    ASSERT_EQ(10, counter.LengthOfLongestWord());
}

TEST(WordCounterTests, GivenOneFileWith3RepeatedWords_WhenFrequencyIsQueried_ShouldBe3)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one two two three three three four");
    WordCounter counter(directory.Name());
    ASSERT_EQ(3, counter.Frequency("three"));
}

TEST(WordCounterTests, GivenOneFileWithWordsRepeatedInDifferentCase_WhenFrequencyIsQueried_CountShouldBeReportedAgainstLowerCaseWord)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one ONE OnE oNe");
    WordCounter counter(directory.Name());
    ASSERT_EQ(4, counter.Frequency("one"));
}

TEST(WordCounterTests, GivenOneFileWith10WordsOnMultipleLines_WhenWordsAreCounted_ShouldBe10)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "\r\none two three fours five six\r\n \r\nseven eight nine \r\n\r\nten\r\n");
    WordCounter counter(directory.Name());
    ASSERT_EQ(10, counter.WordCount());
}