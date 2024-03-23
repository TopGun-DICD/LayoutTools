#include "LayoutReader_OASIS.hpp"

#include <ctime>

// https://github.com/klayoutmatthias/dump_oas_gds2

LayoutReader_OASIS::LayoutReader_OASIS() : p_activeLibrary(nullptr), p_activeElement(nullptr), p_activeItem(nullptr) {

}

bool LayoutReader_OASIS::IsMyFormat(const STR_CLASS &fName) {
  fileName = fName;

  if (fName.substr(fName.find_last_of(STR_VALUE(".")) + 1) != STR_VALUE("oa"))
    if (fName.substr(fName.find_last_of(STR_VALUE(".")) + 1) != STR_VALUE("oas"))
      return false;

  return true;
}

bool LayoutReader_OASIS::Read(Layout *layout) {
  if (!layout)
    return false;
  p_layout = layout;

  return false;

  file.open(fileName, std::ios::in | std::ios::binary);
  if (!file.is_open())
    return false;

}

