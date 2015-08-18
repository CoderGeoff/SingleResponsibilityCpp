#include "stdafx.h"
#include "TemporaryFile.h"
#include <sstream>
#include <string>
#include <stdio.h> 

TemporaryFile::TemporaryFile(const std::string& parentDirectory, const std::string& contents)
{
    char fileName[L_tmpnam];
    tmpnam_s(fileName, L_tmpnam);

    std::string filePath = parentDirectory + fileName;

    FILE* file = nullptr;
    errno_t result = fopen_s(&file, filePath.c_str(), "w");
    if (result != 0)
        ThrowError("fopen", perror);

    if (fputs(contents.c_str(), file) == EOF)
        ThrowError("fputs", ferror);

    fclose(file);

    m_Name = fileName;
}


const std::string& TemporaryFile::Name() const
{
    return m_Name;
}

template <class T>
void TemporaryFile::ThrowError(const char* errorApiCall, T diagnosticInfo)
{
    std::stringstream errorBuilder;
    errorBuilder << "Error " << diagnosticInfo << " from " << errorApiCall;
    throw std::exception(errorBuilder.str().c_str());
}

