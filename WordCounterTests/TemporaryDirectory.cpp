#include "stdafx.h"
#include "TemporaryDirectory.h"
#include <sstream>
#include <string>
#include <windows.h>
#include <stdio.h> 
#include <direct.h>

TemporaryDirectory::TemporaryDirectory()
{
    std::string directoryPath = GetTemporaryPath() + GetTemporaryFileName();

    if (_mkdir(directoryPath.c_str()) == -1)
        ThrowError("_mkdir", perror);

    m_Name = directoryPath;
}


const std::string& TemporaryDirectory::Name() const
{
    return m_Name;
}

std::string TemporaryDirectory::GetTemporaryPath()
{
    char directoryNameBuffer[260];
    DWORD bufferLength;
    bufferLength = GetTempPathA(MAX_PATH, directoryNameBuffer);
    if (bufferLength == 0)
        ThrowError("GetTempPathA", GetLastError());
    return std::string(directoryNameBuffer);
}

std::string TemporaryDirectory::GetTemporaryFileName()
{
    char temporaryName[L_tmpnam];
    tmpnam_s(temporaryName, L_tmpnam);
    return std::string(temporaryName);
}

template <class T>
void TemporaryDirectory::ThrowError(const char* errorApiCall, T diagnosticInfo)
{
    std::stringstream errorBuilder;
    errorBuilder << "Error " << diagnosticInfo << " from " << errorApiCall;
    throw std::exception(errorBuilder.str().c_str());
}

