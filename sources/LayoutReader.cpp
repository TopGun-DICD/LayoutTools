#include "LayoutReader.hpp"

BaseLayoutReader::BaseLayoutReader() : p_data(nullptr) {}

BaseLayoutReader *GetReader(const std::string &fName) {
  BaseLayoutReader *p_reader = nullptr;

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

void FreeReader(BaseLayoutReader *reader) {
  if (!reader)
    return;
  delete reader;
  reader = nullptr;
}
