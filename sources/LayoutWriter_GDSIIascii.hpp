/*
 * LayoutWriter_GDSIIascii.hpp
 *
 * Calma ASCII GDSII file format writer by Artem K. Efremov
 * 20.03.2021
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
