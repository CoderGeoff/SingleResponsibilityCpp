#include "stdafx.h"
#include <memory>

#include <gtest/gtest.h>
#include "TemporaryDirectory.h"
#include "TemporaryFile.h"
#include "DirectoryLexicalAnalyzer.h"

TEST(WordCounterTests, GivenAnEmptyDirectory_WhenWordsAreCounted_ShouldBeZero)
{
    TemporaryDirectory directory;
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(0, counter.WordCount());
}

TEST(WordCounterTests, GivenAnEmptyDirectory_WhenLongestWordIsQueried_LengthShouldBeZero)
{
    TemporaryDirectory directory;
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(0, counter.LengthOfLongestWord());
}

TEST(WordCounterTests, GivenAnEmptyDirectory_WhenWordFrequencyIsQueried_ShouldBeZero)
{
    TemporaryDirectory directory;
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(0, counter.Frequency("the"));
}

TEST(WordCounterTests, GivenOneFileWith5Words_WhenWordsAreCounted_ShouldBe5)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one two three four five");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(5, counter.WordCount());
}

TEST(WordCounterTests, GivenOneFileWith10LetterWordWords_WhenLongestWordIsQueried_ShouldBe10)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one two vegetarian three four five");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(10, counter.LengthOfLongestWord());
}

TEST(WordCounterTests, GivenOneFileWith3RepeatedWords_WhenFrequencyIsQueried_ShouldBe3)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one two two three three three four");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(3, counter.Frequency("three"));
}

TEST(WordCounterTests, GivenOneWordWithDifferentFirstLetterCapitalization_WhenFrequencyIsQueried_CountShouldBeReportedAgainstLowerCaseWord)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one One");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(2, counter.Frequency("one"));
}

TEST(WordCounterTests, GivenOneWordWithDifferentCapitalization_WhenFrequencyIsQueried_ShouldBeCountedAsDifferentWords)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "who WHO");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(1, counter.Frequency("who"));
}

TEST(WordCounterTests, GivenAWordInDoubleQuotes_WhenFrequencyIsQueried_ShouldBeCountedWithTheUnquotedWord)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one \"one\"");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(2, counter.Frequency("one"));
}

TEST(WordCounterTests, GivenAWordInSingleQuotes_WhenFrequencyIsQueried_ShouldBeCountedWithTheUnquotedWord)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "one 'one'");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(2, counter.Frequency("one"));
}

TEST(WordCounterTests, GivenAWordInDoubleQuotes_WhenWordLengthIsQueried_ShouldIgnoreTheQuotes)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "\"one\"");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(3, counter.LengthOfLongestWord());
}

TEST(WordCounterTests, GivenWordsWithApostrophes_WhenQueried_CountShouldCountThemAsIndependentWords)
{
    // Given
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "ones one one's");

    // When
    DirectoryLexicalAnalyzer counter(directory.Name());
    std::stringstream resultBuilder;
    resultBuilder << "ones: " << counter.Frequency("ones") << ", ";
    resultBuilder << "one: " << counter.Frequency("one") << ", ";
    resultBuilder << "one's: " << counter.Frequency("one's");
    std::string result = resultBuilder.str();

    // Then
    ASSERT_EQ("ones: 1, one: 1, one's: 1", result);
}

TEST(WordCounterTests, GivenAWordEndingInPunctuation_WhenWordLengthIsQueried_ShouldIgnorePunctuation)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "Hello world!!!");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(5, counter.LengthOfLongestWord());
}

TEST(WordCounterTests, GivenPunctuationSurroundedByWhitespace_WhenWordCountIsQueried_ShouldIgnoreWordsConsistingOnlyOfPunctuation)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "Hello , world !!!");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(2, counter.WordCount());
}

TEST(WordCounterTests, GivenOneFileWith10WordsOnMultipleLines_WhenWordsAreCounted_ShouldBe10)
{
    TemporaryDirectory directory;
    TemporaryFile file(directory.Name(), "\r\none two three fours five six\r\n \r\nseven eight nine \r\n\r\nten\r\n");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(10, counter.WordCount());
}

TEST(WordCounterTests, GivenTwoFilesWith5WordsEach_WhenWordsAreCounted_ShouldBe10)
{
    TemporaryDirectory directory;
    TemporaryFile file1(directory.Name(), "one two three four five");
    TemporaryFile file2(directory.Name(), "one two three four five");
    DirectoryLexicalAnalyzer counter(directory.Name());
    ASSERT_EQ(10, counter.WordCount());
}