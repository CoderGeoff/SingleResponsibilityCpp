#include "stdafx.h"
#include "TemporaryDirectory.h"
#include <sstream>
#include <string>
#include <windows.h>
#include <stdio.h> 
#include <direct.h>

TemporaryDirectory::TemporaryDirectory()
{
    char directoryNameBuffer[MAX_PATH];
    DWORD bufferLength = GetTempPathA(MAX_PATH, directoryNameBuffer);

    if (bufferLength == 0)
        ThrowError("GetTempPathA", GetLastError());

    tmpnam_s(directoryNameBuffer + bufferLength, MAX_PATH - bufferLength);

    if (_mkdir(directoryNameBuffer) == -1)
        ThrowError("_mkdir", perror);

    m_Name = directoryNameBuffer;
}

void TemporaryDirectory::DeleteFilesRecursiveInDirectory(const std::string& directory)
{
    HANDLE searchHandle;
    WIN32_FIND_DATAA findResult;

    if ((searchHandle = FindFirstFileA((directory + "/*").c_str(), &findResult)) == INVALID_HANDLE_VALUE)
        ThrowError("FindFirstFileA", GetLastError());

    do {
        std::string fileName = directory + "/" + findResult.cFileName;
        bool isDirectory = (findResult.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        bool isCurrentDirectory = std::string(".") == findResult.cFileName;
        bool isParentDirectory = std::string("..") == findResult.cFileName;

        if (isCurrentDirectory || isParentDirectory) 
            continue;

        if (isDirectory)
            DeleteFilesRecursiveInDirectory(fileName);

        if (std::remove(fileName.c_str()) != 0)
            ThrowError("std::remove", "");

    } while (FindNextFileA(searchHandle, &findResult));

    FindClose(searchHandle);

    if (std::remove(m_Name.c_str()) != 0)
        ThrowError("std::remove", "");
}

TemporaryDirectory::~TemporaryDirectory()
{
}

const std::string& TemporaryDirectory::Name() const
{
    return m_Name;
}

template <class T>
void TemporaryDirectory::ThrowError(const char* errorApiCall, T diagnosticInfo)
{
    std::stringstream errorBuilder;
    errorBuilder << "Error " << diagnosticInfo << " from " << errorApiCall;
    throw std::exception(errorBuilder.str().c_str());
}

