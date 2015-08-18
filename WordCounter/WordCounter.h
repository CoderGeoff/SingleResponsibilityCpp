#pragma once
#include <string>

class WordCounter
{
    std::string m_DirectoryName;
    bool m_IsInitialized;
    void LazyInitialize() const;
    void Initialize();
public:
    explicit WordCounter(const std::string& directoryName);
    size_t WordCount() const;
    size_t LengthOfLongestWord() const;
    size_t Frequency(std::string word) const;
};

