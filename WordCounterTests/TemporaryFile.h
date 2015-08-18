#pragma once
#include <string>

class TemporaryFile
{
public:
    std::string m_Name;
    template <class T> static void ThrowError(const char* errorApiCall, T diagnosticInfo);

public:
    TemporaryFile::TemporaryFile(const std::string& parentDirectory, const std::string& contents);
    const std::string& Name() const;
};

