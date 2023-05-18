#pragma once

#include <string>

#include "LayoutWriter.hpp"
#include "Layout.hpp"

class LayoutWriter_CIF : public LayoutWriter {
public:
  LayoutWriter_CIF();
public:
  bool Write(const STR_CLASS &fileName, Layout* layout) final;
private:
};

