#include <iostream>

#include "LayoutData.hpp"
#include "LayoutReader.hpp"

int main(int argc, char *argv[]) {
  LayoutData  layout;

  AbstractLayoutReader *p_reader = GetReader(std::string("tests/inv.gds"));
  if (!p_reader)
    return EXIT_FAILURE;

  if (!p_reader->Read(&layout)) {
    FreeReader(p_reader);
    return EXIT_FAILURE;
  }

  FreeReader(p_reader);
  return EXIT_SUCCESS;
}
