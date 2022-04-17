#include "LayoutReader_DXF.hpp"

#include <ctime>

LayoutReader_DXF::LayoutReader_DXF() : p_activeLibrary(nullptr), p_activeElement(nullptr), p_activeItem(nullptr) {

}

bool LayoutReader_DXF::IsMyFormat(const std::wstring &fName) {
  fileName = fName;

  if (fName.substr(fName.find_last_of(L".") + 1) == L"cif")
    return true;


  return false;
}

bool LayoutReader_DXF::Read(Layout *layout) {
  if (!layout)
    return false;
  p_layout = layout;

  return false;

  file.open(fileName, std::ios::in | std::ios::binary);
  if (!file.is_open())
    return false;

}

