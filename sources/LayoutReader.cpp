#include "LayoutReader.hpp"

LayoutReader::LayoutReader() : p_data(nullptr) {}

LayoutReader *GetReader(const std::string &fName) {
  LayoutReader *p_reader = nullptr;

  p_reader = new LayoutReader_GDSIIBin;
  if (p_reader->IsMyFormat(fName))
    return p_reader;
  delete p_reader;
  p_reader = nullptr;

  p_reader = new LayoutReader_MSK;
  if (p_reader->IsMyFormat(fName))
    return p_reader;
  delete p_reader;
  p_reader = nullptr;

  return p_reader;
}

void FreeReader(LayoutReader *reader) {
  if (!reader)
    return;
  delete reader;
  reader = nullptr;
}
