#include "MonitoredInputStream.h"

MonitoredInputStream::MonitoredInputStream(std::shared_ptr<std::istream> inputStream)
    : m_InputStream(inputStream)
{
}

size_t MonitoredInputStream::WordCount() const
{
    return 0;
}

size_t MonitoredInputStream::LengthOfLongestWord() const
{
    return 0;
}

size_t MonitoredInputStream::Frequency(std::string word) const
{
    return 0;
}