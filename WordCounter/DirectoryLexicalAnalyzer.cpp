#include "DirectoryLexicalAnalyzer.h"
#include <windows.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

DirectoryLexicalAnalyzer::DirectoryLexicalAnalyzer(const std::string& directoryName)
    : m_DirectoryName(directoryName),
    m_WordCount(0),
    m_LongestWordLength(0),
    m_IsInitialized(false)
{
}

size_t DirectoryLexicalAnalyzer::WordCount() const
{
    LazyInitialize();
    return m_WordCount;
}

size_t DirectoryLexicalAnalyzer::LengthOfLongestWord() const
{
    LazyInitialize();
    return m_LongestWordLength;
}

size_t DirectoryLexicalAnalyzer::Frequency(std::string word) const
{
    LazyInitialize();
    auto wordFinder = m_Frequency.find(word);
    return wordFinder == m_Frequency.end() ? 0 : wordFinder->second;
}

void DirectoryLexicalAnalyzer::LazyInitialize() const
{
    if (m_IsInitialized)
        return;
    const_cast<DirectoryLexicalAnalyzer*>(this)->Initialize();
}

void DirectoryLexicalAnalyzer::Initialize()
{
    std::vector <std::string> fileNames = GetFiles();
    for (auto fileNameIter = fileNames.begin(); fileNameIter != fileNames.end(); ++fileNameIter)
    {
        std::fstream file;
        file.open(*fileNameIter, std::ios_base::in);
        while (!file.eof())
        {
            std::string word;
            file >> word;


            if (word.length() > 0)
            {

                // we lower case the first letter, unless there are capitals inside the word
                // in which case we assume that it's some kind of abbreviation
                if (std::all_of(word.begin() + 1, word.end(), ::islower))
                    transform(word.begin(), word.end(), word.begin(), ::tolower);

                m_WordCount++;
                m_Frequency[word]++;
                m_LongestWordLength = max(word.length(), m_LongestWordLength);
            }
        }
    }
    m_IsInitialized = true;
}

std::vector<std::string> DirectoryLexicalAnalyzer::GetFiles() const
{
    std::vector<std::string> files;

    HANDLE searchHandle;
    WIN32_FIND_DATAA findResult;

    if ((searchHandle = FindFirstFileA((m_DirectoryName + "/*").c_str(), &findResult)) == INVALID_HANDLE_VALUE)
        ThrowError("FindFirstFileA", GetLastError());

    do {
        bool isDirectory = (findResult.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        if (!isDirectory)
        {
            std::string fileName = m_DirectoryName + "/" + findResult.cFileName;
            files.push_back(fileName);
        }
    } while (FindNextFileA(searchHandle, &findResult));

    FindClose(searchHandle);
    return files;
}

template <class T>
void DirectoryLexicalAnalyzer::ThrowError(const char* errorApiCall, T diagnosticInfo)
{
    std::stringstream errorBuilder;
    errorBuilder << "Error " << diagnosticInfo << " from " << errorApiCall;
    throw std::exception(errorBuilder.str().c_str());
}