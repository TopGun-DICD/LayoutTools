#include "LayoutWriter.hpp"

LayoutWriter::LayoutWriter() {}

LayoutWriter *GetWriter(const std::string &format) {
  if (format == "gdsiibin")
    return  new LayoutWriter_GDSIIBin;

  return nullptr;
}

void FreeWriter(LayoutWriter *writer) {
  if (!writer)
    return;
  delete writer;
  writer = nullptr;
}
