#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutWriter.hpp"
#include "LayoutData.hpp"

class LayoutWriter_MSK : public LayoutWriter {
public:
  LayoutWriter_MSK();
public:
  bool Write(std::wstring fileName, LayoutData *layout) final;
private:
};
