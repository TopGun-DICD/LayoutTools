#include <iostream>

#include "LayoutData.hpp"
#include "LayoutReader.hpp"

int main(int argc, char *argv[]) {
  LayoutData  layout;

  //AbstractLayoutReader *p_reader = GetReader(std::string("tests/inv.gds"));
  AbstractLayoutReader *p_reader = GetReader(std::string("tests/nand2.gds"));
  //AbstractLayoutReader *p_reader = GetReader(std::string("tests/xor.gds"));
  if (!p_reader)
    return EXIT_FAILURE;
  if (!p_reader->Read(&layout)) {
    FreeReader(p_reader);
    return EXIT_FAILURE;
  }
  FreeReader(p_reader);

  std::cout << "Input file has " << layout.libraries.size() << " libraries" << std::endl;
  
  for (size_t i = 0; i < layout.libraries.size(); ++i) {
    std::cout << "  - Library [" << i << "] has name '" << layout.libraries[i]->name << "' and contains " << layout.libraries[i]->elements.size() << " elements:" << std::endl;
    for(size_t j = 0; j < layout.libraries[i]->elements.size(); ++j)
      std::cout << "    * " << layout.libraries[i]->elements[j]->name << " (contains " << layout.libraries[i]->elements[j]->items.size() << " geometries)" << std::endl;
    std::cout << "    Library [" << i << "] also contains " << layout.libraries[i]->layers.size() << " layers (in order of appearance):" << std::endl;
    for (size_t j = 0; j < layout.libraries[i]->layers.size(); ++j)
      std::cout << "    * " << layout.libraries[i]->layers[j].layer << std::endl;
  }

  return EXIT_SUCCESS;
}
