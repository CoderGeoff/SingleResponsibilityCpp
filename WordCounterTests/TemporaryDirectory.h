#pragma once
#include <string>

class TemporaryDirectory
{
    std::string m_Name;
    void DeleteFilesRecursiveInDirectory(const std::string& directory);
    template <class T> void ThrowError(const char* errorApiCall, T diagnosticInfo);

public:
    TemporaryDirectory();
    ~TemporaryDirectory();
    const std::string& Name() const;
};

