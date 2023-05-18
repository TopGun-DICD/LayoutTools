#include <iostream>
#include <iomanip>

#include "Layout.hpp"
#include "LayoutReader.hpp"
#include "LayoutWriter.hpp"
#include "LayoutProcessing.hpp"

int main(int argc, char *argv[]) {
  Layout  layout;

  //std::wstring fileName = L"tests/inv.gds";
  //std::wstring fileName = L"tests/4004.gds";
  //std::wstring fileName = L"tests/passive.gds";
  //std::wstring fileName = L"output.gds";
  //std::wstring fileName = L"tests/nand2.gds";
  //std::wstring fileName = L"tests/xor.gds";
  //std::wstring fileName = L"tests/1Kpolyg.gds";
  //std::wstring fileName = L"tests/testDesign.gds";
  //std::wstring fileName = L"tests/cmos.msk";
  //std::wstring fileName = L"tests/inv.msk";
  
  //std::wstring fileName = L"tests/xor.gds.txt";

  if (argc != 2) {
    std::cerr << "Argument (gdsii layout file name) was not passed" << std::endl;
    return EXIT_FAILURE;
  }
  std::string fname = argv[1];
  std::wstring fileName(fname.begin(), fname.end());

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

  /*
  std::wcout << "Input file " << fileName << " has " << layout.libraries.size() << " library(ies)" << std::endl;

  for (size_t i = 0; i < layout.libraries.size(); ++i) {
    std::cout << "  - Library [" << i << "] has name '" << layout.libraries[i]->name << "' and contains " << layout.libraries[i]->elements.size() << " elements:" << std::endl;
    for(size_t j = 0; j < layout.libraries[i]->elements.size(); ++j)
      std::cout << "      * " << layout.libraries[i]->elements[j]->name << " (contains " << layout.libraries[i]->elements[j]->geometries.size() << " geometries)" << std::endl;
    std::cout << "    Library [" << i << "] also contains " << layout.libraries[i]->layers.size() << " layers (in order of appearance):" << std::endl;
    //std::cout << "      { ";
    for (size_t j = 0; j < layout.libraries[i]->layers.size(); ++j)
      std::cout << std::setw(5) << layout.libraries[i]->layers[j].layer << " [" << layout.libraries[i]->layers[j].dataType << "]" << std::endl;
    //std::cout << " }" << std::endl;
  }
  //*/
  
  std::wcout << "<Cell name>;<Geometries>;<Area>;<most difficult polygon>" << std::endl;
  
  for (size_t i = 0; i < layout.libraries.size(); ++i) {
    for (size_t j = 0; j < layout.libraries[i]->elements.size(); ++j) {
      std::cout << "Cell name = " << layout.libraries[i]->elements[j]->name
                << " Geometries = " << layout.libraries[i]->elements[j]->geometries.size()
                << " Cell area = " << (int64_t)(layout.libraries[i]->elements[j]->max.x - layout.libraries[i]->elements[j]->min.x) * (int64_t)(layout.libraries[i]->elements[j]->max.y - layout.libraries[i]->elements[j]->min.y);
      //std::cout << layout.libraries[i]->elements[j]->name << ";" << layout.libraries[i]->elements[j]->geometries.size() << ";"
      //          << (int64_t)(layout.libraries[i]->elements[j]->max.x - layout.libraries[i]->elements[j]->min.x) * (int64_t)(layout.libraries[i]->elements[j]->max.y - layout.libraries[i]->elements[j]->min.y) << ";";
      size_t points = 0;
      for (size_t k = 0; k < layout.libraries[i]->elements[j]->geometries.size(); ++k) {
        if (layout.libraries[i]->elements[j]->geometries[k]->coords.size() > points)
          points = layout.libraries[i]->elements[j]->geometries[k]->coords.size();
      }
      std::cout << " Max points = "  << points << std::endl;
    }
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
