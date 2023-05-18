/*
 * LayoutWriter_DXF.cpp
 *
 * DXF file format writer by <author>
 * <date>
 */

#include "LayoutWriter_DXF.hpp"
#include "GDSIIHelperFunctions.hpp"

#include <ctime>
#include "GDSIITypes.hpp"

LayoutWriter_DXF::LayoutWriter_DXF() {

}

bool LayoutWriter_DXF::Write(const STR_CLASS &fileName, Layout *layout) {
  if (!layout)
    return false;
  
  return false;
}


