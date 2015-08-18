#include "WordCounter.h"

void WordCounter::LazyInitialize() const
{
    if (m_IsInitialized)
        return;
    const_cast<WordCounter*>(this)->Initialize();
}

void WordCounter::Initialize()
{

    m_IsInitialized = true;
}

WordCounter::WordCounter(const std::string& directoryName)
    : m_DirectoryName(directoryName),
    m_IsInitialized(false)
{
}

size_t WordCounter::WordCount() const
{
    LazyInitialize();
    return 0;
}

size_t WordCounter::LengthOfLongestWord() const
{
    return 0;
}

size_t WordCounter::Frequency(std::string word) const
{
    return 0;
}