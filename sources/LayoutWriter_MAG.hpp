#pragma once

#include <string>

#include "LayoutWriter.hpp"
#include "Layout.hpp"

class LayoutWriter_MAG : public LayoutWriter {
public:
  LayoutWriter_MAG();
public:
  bool Write(const STR_CLASS &fileName, Layout *layout) final;
private:
};

