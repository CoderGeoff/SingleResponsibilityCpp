#pragma once
#include <string>

class TemporaryDirectory
{
    std::string m_Name;
    template <class T> static void ThrowError(const char* errorApiCall, T diagnosticInfo);
    static std::string GetTemporaryPath();
    static std::string GetTemporaryFileName();

public:
    TemporaryDirectory();
    const std::string& Name() const;
};

