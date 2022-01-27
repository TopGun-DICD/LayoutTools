#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutWriter.hpp"
#include "LayoutData.hpp"

class LayoutWriter_GDSIIascii : public LayoutWriter {
public:
  LayoutWriter_GDSIIascii();
public:
  bool Write(std::wstring fileName, LayoutData *layout) final;
private:
};
