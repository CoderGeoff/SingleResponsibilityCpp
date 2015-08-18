#pragma once
#include <istream>
#include <memory>

class MonitoredInputStream 
{
    std::shared_ptr<std::istream> m_InputStream;
public:
    explicit MonitoredInputStream::MonitoredInputStream(std::shared_ptr<std::istream> inputStream);
    template<class T>
    MonitoredInputStream& operator >> (T& val);

    size_t WordCount() const;
    size_t LengthOfLongestWord() const;
    size_t Frequency(std::string word) const;
};

template <class T>
MonitoredInputStream& MonitoredInputStream::operator>>(T& val)
{
    *m_InputStream >> val;
    return *this;
}
