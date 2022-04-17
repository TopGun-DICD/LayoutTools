/*
 * LayoutWriter_GDSIIBin.cpp
 *
 * MSK file format writer by <author>
 * <date>
 */

#include "LayoutWriter_MSK.hpp"
#include "GDSIIHelperFunctions.hpp"

#include <ctime>
#include "GDSIITypes.hpp"

LayoutWriter_MSK::LayoutWriter_MSK() {

}

bool LayoutWriter_MSK::Write(std::wstring fileName, Layout *layout) {
  if (!layout)
    return false;
  
  return false;
}


