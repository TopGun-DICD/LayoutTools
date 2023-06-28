/*
 * LayoutWriter_GDSIIascii.cpp
 *
 * Calma ASCII GDSII file format writer by Artem K. Efremov
 * 20.03.2021
 */

#include "LayoutWriter_GDSIIascii.hpp"
#include "GDSIIHelperFunctions.hpp"

#include <ctime>
#include "GDSIITypes.hpp"

LayoutWriter_GDSIIascii::LayoutWriter_GDSIIascii() {

}

bool LayoutWriter_GDSIIascii::Write(const STR_CLASS &fileName, Layout *layout) {
  if (!layout)
    return false;

  return false;
}