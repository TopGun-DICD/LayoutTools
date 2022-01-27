#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutData.hpp"

class LayoutWriter {
protected:
  LayoutData   *p_data;
  std::ofstream file;
public:
  LayoutWriter();
public:
  virtual bool Write(std::wstring fileName, LayoutData *layout) = 0;
};

LayoutWriter *GetWriter(LayoutFileFormat format);
void FreeWriter(LayoutWriter *ptr);