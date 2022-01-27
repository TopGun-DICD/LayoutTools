#pragma once

#include "LayoutData.hpp"

LayoutData *ReadLayoutFromFile(std::wstring filename);
void ReadLayoutFromFile(std::wstring filename, LayoutData *layout);
bool CopyLayout(const LayoutData *src, LayoutData *dst);
