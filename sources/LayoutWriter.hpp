#pragma once

#include <string>
#include <fstream>

#include "Layout.hpp"

#include "LinuxCompat.hpp"

class LayoutWriter {
protected:
  Layout       *p_data;
  std::ofstream file;
public:
  LayoutWriter();
public:
  virtual bool Write(const STR_CLASS &fileName, Layout *layout) = 0;
};

LayoutWriter *GetWriter(FileFormat format);
void FreeWriter(LayoutWriter *ptr);