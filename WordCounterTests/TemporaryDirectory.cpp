#include "stdafx.h"
#include "TemporaryDirectory.h"
#include <string>

TemporaryDirectory::TemporaryDirectory()
{
    m_Name = "C:\\Temp\\7AD3AB94-1BAA-4AAC-9E83-C061D73DFE2D";
}

TemporaryDirectory::~TemporaryDirectory()
{
}

const std::string& TemporaryDirectory::Name() const
{
    return m_Name;
}