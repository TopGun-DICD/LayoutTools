#pragma once

#include "Layout.hpp"

Layout *ReadLayoutFromFile(const STR_CLASS &filename);
void ReadLayoutFromFile(const STR_CLASS &filename, Layout *layout);
bool CopyLayout(const Layout *src, Layout *dst);
