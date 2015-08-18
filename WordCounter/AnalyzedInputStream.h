#pragma once
#include <istream>
#include <memory>

class AnalyzedInputStream 
{
    std::shared_ptr<std::istream> m_InputStream;
public:
    explicit AnalyzedInputStream::AnalyzedInputStream(std::shared_ptr<std::istream> inputStream);
    template<class T>
    AnalyzedInputStream& operator >> (T& val);

    size_t WordCount() const;
    size_t LengthOfLongestWord() const;
    size_t Frequency(std::string word) const;
};

template <class T>
AnalyzedInputStream& AnalyzedInputStream::operator>>(T& val)
{
    *m_InputStream >> val;
    return *this;
}
