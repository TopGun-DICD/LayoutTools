#include "LayoutReader_CIF.hpp"

#include <ctime>

// https://www.layouteditor.org/layout/file-formats/cif
// http://www.srware.com/manual/xicmanual/node757.html
// http://www.vlsitechnology.org/html/linux_help6.html
// https://ece.k-state.edu//people/faculty/kuhn/files/MagicAndCIFfileFormats.PDF
// https://authors.library.caltech.edu/27019/1/TR_2686.pdf

LayoutReader_CIF::LayoutReader_CIF() : p_activeLibrary(nullptr), p_activeElement(nullptr), p_activeItem(nullptr) {

}

bool LayoutReader_CIF::IsMyFormat(const STR_CLASS &fName) {
  fileName = fName;

  if (fName.substr(fName.find_last_of(STR_VALUE(".")) + 1) == STR_VALUE("cif"))
    return true;


  return false;
}

bool LayoutReader_CIF::Read(Layout *layout) {
  if (!layout)
    return false;
  p_layout = layout;

  return false;

  file.open(fileName, std::ios::in | std::ios::binary);
  if (!file.is_open())
    return false;

}

