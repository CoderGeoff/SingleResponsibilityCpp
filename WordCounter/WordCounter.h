#pragma once
#include <string>

class WordCounter
{
    std::string m_DirectoryName;
public:
    explicit WordCounter(const std::string& directoryName);
    size_t WordCount();
};

