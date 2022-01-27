#include <iostream>

#include "LayoutData.hpp"
#include "LayoutReader.hpp"
#include "LayoutWriter.hpp"
#include "LayoutProcessing.hpp"

int main(int argc, char *argv[]) {
  LayoutData  layout;

  //std::wstring fileName = L"tests/inv.gds";
  //std::wstring fileName = L"output.gds";
  //std::wstring fileName = L"tests/nand2.gds";
  //std::wstring fileName = L"tests/xor.gds";
  //std::wstring fileName = L"tests/1Kpolyg.gds";
  //std::wstring fileName = L"tests/testDesign.gds";
  std::wstring fileName = L"tests/cmos.msk";

  LayoutReader *p_reader = GetReader(fileName);
  if (!p_reader) {
    std::wcerr << "__err__ : Can't file appropriate reader for given file '" << fileName << "'." << std::endl;
    return EXIT_FAILURE;
  }
  if (!p_reader->Read(&layout)) {
    std::wcerr << "__err__ : Can't read file '" << fileName << "'." << std::endl;
    FreeReader(p_reader);
    return EXIT_FAILURE;
  }
  FreeReader(p_reader);

  std::wcout << "Input file " << fileName << " has " << layout.libraries.size() << " library(ies)" << std::endl;

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
  LayoutWriter *p_writer = GetWriter(LayoutFileFormat::GDSII_bin);
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
