#include "stdafx.h"
#include <memory>

#include <gtest/gtest.h>
#include "TemporaryDirectory.h"
#include <WordCounter.h>

TEST(WordCounterTests, GivenAnEmptyDirectory_WhenWordsAreCounted_ShouldBeZero)
{
    TemporaryDirectory directory;
    WordCounter counter(directory.Name());
    ASSERT_EQ(0, counter.WordCount());
}