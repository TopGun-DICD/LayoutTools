/*
 * LayoutReader.hpp
 *
 * Layout formats implementation:
 * GDSII Binary - Dmitry A. Bulakh
 * MSK          - Mikhail S. Kotlyarov 
 */
#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutReader.hpp"
#include "LayoutData.hpp"
#include "GDSIITypes.hpp"

class LayoutReader_GDSIIascii : public LayoutReader {
  Library      *p_activeLibrary;
  Element      *p_activeElement;
  Geometry     *p_activeGeometry;
public:
  LayoutReader_GDSIIascii();
public:
  bool IsMyFormat(const std::string &fName) final;
  bool Read(LayoutData *layout) final;
private:
};
