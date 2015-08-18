#include "AnalyzedInputStream.h"

AnalyzedInputStream::AnalyzedInputStream(std::shared_ptr<std::istream> inputStream)
    : m_InputStream(inputStream)
{
}

size_t AnalyzedInputStream::WordCount() const
{
    return 0;
}

size_t AnalyzedInputStream::LengthOfLongestWord() const
{
    return 0;
}

size_t AnalyzedInputStream::Frequency(std::string word) const
{
    return 0;
}