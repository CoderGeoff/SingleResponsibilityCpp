#pragma once
#include <string>
#include <vector>
#include <map>

class DirectoryLexicalAnalyzer
{
    std::string m_DirectoryName;
    size_t m_WordCount;
    size_t m_LongestWordLength;
    bool m_IsInitialized;
    std::map < std::string, size_t> m_Frequency;

    void LazyInitialize() const;
    void Initialize();
    std::vector<std::string> GetFiles() const;
    template <class T> static void ThrowError(const char* errorApiCall, T diagnosticInfo);
    static std::string GetWordWithoutSurroundingPunctuation(const std::string& word, const std::string& punctuationSymbols);

public:
    explicit DirectoryLexicalAnalyzer(const std::string& directoryName);
    size_t WordCount() const;
    size_t LengthOfLongestWord() const;
    size_t Frequency(std::string word) const;
};

