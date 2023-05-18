/*
 * LayoutReader.hpp
 *
 * Layout formats implementation:
 * GDSII Binary - Dmitry A. Bulakh
 *                see LayoutReader_GDSIIbin.hpp
 * GDSII ASCII  - Artem K. Efremov
 *                see LayoutReader_GDSascii
 * MSK          - Mikhail S. Kotlyarov  
 *                see LayoutReader_MSK.hpp
 */
#pragma once

#include <string>
#include <fstream>

#include "Layout.hpp"

#include "LinuxCompat.hpp"

class LayoutReader {
protected:
  STR_CLASS     fileName;
  Layout       *p_layout;
  std::ifstream file;
public:
  LayoutReader();
public:
  virtual bool IsMyFormat(const STR_CLASS &fName) = 0;
  virtual bool Read(Layout *layout) = 0;
};

LayoutReader * GetReader(const STR_CLASS &fName);
void FreeReader(LayoutReader *ptr);
