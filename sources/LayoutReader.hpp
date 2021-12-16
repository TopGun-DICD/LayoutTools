/*
 * LayoutReader.hpp
 *
 * Layout formats implementation:
 * GDSII Binary - Dmitry A. Bulakh
 *                see LayoutReader_GDSIIBin.hpp
 * MSK          - Mikhail S. Kotlyarov  
 *                see LayoutReader_MSK.hpp
 */
#pragma once

#include <string>
#include <fstream>

#include "LayoutData.hpp"

class LayoutReader {
protected:
  std::string   fileName;
  LayoutData   *p_data;
  std::ifstream file;
public:
  LayoutReader();
public:
  virtual bool IsMyFormat(const std::string &fName) = 0;
  virtual bool Read(LayoutData *layout) = 0;
};

LayoutReader*GetReader(const std::string &fName);
void FreeReader(LayoutReader*ptr);
