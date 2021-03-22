#include "LayoutWriter.hpp"

AbstractLayoutWriter::AbstractLayoutWriter() {}

AbstractLayoutWriter *GetWriter(const std::string &format) {
  if (format == "gdsiibin")
    return  new GDSIIBinaryWriter;

  return nullptr;
}

void FreeWriter(AbstractLayoutWriter *writer) {
  if (!writer)
    return;
  delete writer;
  writer = nullptr;
}
