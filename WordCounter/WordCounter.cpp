#include "WordCounter.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <algorithm>

WordCounter::WordCounter(const std::string& directoryName)
    : m_DirectoryName(directoryName),
    m_WordCount(0),
    m_LongestWordLength(0),
    m_IsInitialized(false)
{
}

size_t WordCounter::WordCount() const
{
    LazyInitialize();
    return m_WordCount;
}

size_t WordCounter::LengthOfLongestWord() const
{
    LazyInitialize();
    return m_LongestWordLength;
}

size_t WordCounter::Frequency(std::string word) const
{
    LazyInitialize();
    auto wordFinder = m_Frequency.find(word);
    return wordFinder == m_Frequency.end() ? 0 : wordFinder->second;
}

void WordCounter::LazyInitialize() const
{
    if (m_IsInitialized)
        return;
    const_cast<WordCounter*>(this)->Initialize();
}

void WordCounter::Initialize()
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
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (word.length() > 0)
            {
                m_WordCount++;
                m_Frequency[word]++;
                m_LongestWordLength = max(word.length(), m_LongestWordLength);
            }
        }
    }
    m_IsInitialized = true;
}

std::vector<std::string> WordCounter::GetFiles() const
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
void WordCounter::ThrowError(const char* errorApiCall, T diagnosticInfo)
{
    std::stringstream errorBuilder;
    errorBuilder << "Error " << diagnosticInfo << " from " << errorApiCall;
    throw std::exception(errorBuilder.str().c_str());
}