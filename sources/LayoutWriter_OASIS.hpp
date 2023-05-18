#pragma once

#include <string>

#include "LayoutWriter.hpp"
#include "Layout.hpp"

class LayoutWriter_OASIS : public LayoutWriter {
public:
  LayoutWriter_OASIS();
public:
  bool Write(const STR_CLASS &fileName, Layout *layout) final;
private:
};

