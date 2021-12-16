/*
 * LayoutReader_GDSIIBin.cpp
 *
 * Calma binary GDS II file format reader by Dmitry A. Bulakh
 * 20.03.2021
 */

#include "LayoutReader_GDSIIascii.hpp"
#include "GDSIIHelperFunctions.hpp"

#include <ctime>

LayoutReader_GDSIIascii::LayoutReader_GDSIIascii() : p_activeLibrary(nullptr), p_activeElement(nullptr), p_activeGeometry(nullptr) {
}

bool LayoutReader_GDSIIascii::IsMyFormat(const std::string &fName) {
  return false;
}

bool LayoutReader_GDSIIascii::Read(LayoutData *layout) {
  if (!layout)
    return false;

  return false;
}

