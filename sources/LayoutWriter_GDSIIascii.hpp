/*
 * LayoutWriter_GDSIIascii.hpp
 *
 * Layout formats implementation:
 * GDSII ASCII - Artem K. Efremov
 */
#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutWriter.hpp"
#include "Layout.hpp"

class LayoutWriter_GDSIIascii : public LayoutWriter {
public:
  LayoutWriter_GDSIIascii();
public:
  bool Write(const STR_CLASS &fileName, Layout *layout) final;
private:
};
