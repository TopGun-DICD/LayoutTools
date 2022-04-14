#pragma once

#include "Layout.hpp"

Layout *ReadLayoutFromFile(std::wstring filename);
void ReadLayoutFromFile(std::wstring filename, Layout *layout);
bool CopyLayout(const Layout *src, Layout *dst);
