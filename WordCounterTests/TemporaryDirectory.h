#pragma once
#include <string>

class TemporaryDirectory
{
    std::string m_Name;
public:
    TemporaryDirectory();
    ~TemporaryDirectory();
    const std::string& Name() const;
};

