/*
 * LayoutWriter_GDSIIBin.cpp
 *
 * Calma binary GDS II file format writer by Dmitry A. Bulakh
 * 20.03.2021
 */

#include "LayoutWriter_MSK.hpp"
#include "GDSIIHelperFunctions.hpp"

#include <ctime>
#include "GDSIITypes.hpp"

LayoutWriter_MSK::LayoutWriter_MSK() {

}

bool LayoutWriter_MSK::Write(std::string fileName, LayoutData *layout) {
  if (!layout)
    return false;
  
  return false;
}


