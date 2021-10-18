#include <iostream>

#include "LayoutData.hpp"
#include "LayoutReader.hpp"
#include "LayoutWriter.hpp"

int main(int argc, char *argv[]) {
  LayoutData  layout;

  std::string fileName = "tests/inv.gds";
  //std::string fileName = "output.gds";
  //std::string fileName = "tests/nand2.gds";
  //std::string fileName = "tests/xor.gds";
  //std::string fileName = "tests/1Kpolyg.gds";
  //std::string fileName = "tests/testDesign.gds";
  //std::string fileName = "tests/cmos.msk";

  BaseLayoutReader *p_reader = GetReader(fileName);
  if (!p_reader) {
    std::cerr << "__err__ : Can't file appropriate reader for given file '" << fileName << "'." << std::endl;
    return EXIT_FAILURE;
  }
  if (!p_reader->Read(&layout)) {
    std::cerr << "__err__ : Can't read file '" << fileName << "'." << std::endl;
    FreeReader(p_reader);
    return EXIT_FAILURE;
  }
  FreeReader(p_reader);

  std::cout << "Input file " << fileName << " has " << layout.libraries.size() << " library(ies)" << std::endl;

  for (size_t i = 0; i < layout.libraries.size(); ++i) {
    std::cout << "  - Library [" << i << "] has name '" << layout.libraries[i]->name << "' and contains " << layout.libraries[i]->elements.size() << " elements:" << std::endl;
    for(size_t j = 0; j < layout.libraries[i]->elements.size(); ++j)
      std::cout << "      * " << layout.libraries[i]->elements[j]->name << " (contains " << layout.libraries[i]->elements[j]->geometries.size() << " geometries)" << std::endl;
    std::cout << "    Library [" << i << "] also contains " << layout.libraries[i]->layers.size() << " layers (in order of appearance):" << std::endl;
    std::cout << "      { ";
    for (size_t j = 0; j < layout.libraries[i]->layers.size(); ++j)
      std::cout << layout.libraries[i]->layers[j].layer << " ";
    std::cout << " }" << std::endl;
  }

  /*
  AbstractLayoutWriter *p_writer = GetWriter("gdsiibin");
  if (!p_writer) {
    std::cerr << "__err__ : Can't file appropriate writer for format  'gdsiibin'." << std::endl;
    return EXIT_FAILURE;
  }
  if (!p_writer->Write("output.gds", &layout)) {
    std::cerr << "__err__ : Can't write file '" << "output.gdsii" << "'." << std::endl;
    FreeWriter(p_writer);
    return EXIT_FAILURE;
  }

  FreeWriter(p_writer);
  //*/

  return EXIT_SUCCESS;
}
