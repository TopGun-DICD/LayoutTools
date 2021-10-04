/*
 * LayoutWriter_GDSIIBin.cpp
 *
 * Calma binary GDS II file format writer by Dmitry A. Bulakh
 * 20.03.2021
 */

#include "LayoutWriter.hpp"
#include "GDSIIHelperFunctions.hpp"

#include <ctime>
#include "GDSIITypes.hpp"

LayoutWriter_GDSIIBin::LayoutWriter_GDSIIBin() {

}

bool LayoutWriter_GDSIIBin::Write(std::string fileName, LayoutData *layout) {
  if (!layout)
    return false;
  
  if (fileName.empty())
    return false;

  //std::clock_t startReading = std::clock();

  file.open(fileName, std::ios::out | std::ios::binary);
  if (!file.is_open())
    return false;

  p_data = layout;

  WriteSection_HEADER();
  WriteSection_BEGINLIBRARY();

  for (size_t i = 0; i < layout->libraries.size(); ++i) {
    WriteSection_LIBNAME(layout->libraries[i]);
    WriteSection_UNITS(layout->libraries[i]);
    for (size_t j = 0; j < layout->libraries[i]->elements.size(); ++j) {
      WriteSection_BEGINSTRUCTURE(layout->libraries[i]->elements[j]);
      WriteSection_STRNAME(layout->libraries[i]->elements[j]);

      for (size_t k = 0; k < layout->libraries[i]->elements[j]->items.size(); ++k) {
        switch (layout->libraries[i]->elements[j]->items[k]->type) {
          case ItemType::boundary:
            WriteSection_BOUNDARY(reinterpret_cast<GeometryItem_Boundary *>(layout->libraries[i]->elements[j]->items[k]));
            break;
          case ItemType::reference:
            WriteSection_SREF(reinterpret_cast<GeometryItem_StructureRef *>(layout->libraries[i]->elements[j]->items[k]));
            break;
          case ItemType::path:
            WriteSection_PATH(reinterpret_cast<GeometryItem_Path *>(layout->libraries[i]->elements[j]->items[k]));
            break;
        }
      }

      WriteSection_ENDSTRUCTURE(layout->libraries[i]->elements[j]);
    }

    WriteSection_ENDLIBRARY(layout->libraries[i]);
  }

  file.close();
  //std::clock_t stopReading = std::clock();

  return true;
}

void LayoutWriter_GDSIIBin::WriteSection_HEADER() {
  Record gdsiiRecord = { sizeof(Record) + sizeof(int16_t) , rt_HEADER , 2 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record)); 
  // Write Data
  int16_t versionNumber = 600;
  DeNormalize_WORD(versionNumber);
  file.write(reinterpret_cast<char *>(&versionNumber), sizeof(int16_t));
}

void LayoutWriter_GDSIIBin::WriteSection_BEGINLIBRARY() {
  Record gdsiiRecord = { sizeof(Record) + 2 * sizeof(DateTime) , rt_BGNLIB , 2};
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // Write Data
  DateTime lastTimeAccessed = { 2005,  3, 17, 14, 20, 51 };
  DateTime lastTimeModified = lastTimeAccessed;
  DeNormalize_WORD(lastTimeModified.year);
  DeNormalize_WORD(lastTimeModified.month);
  DeNormalize_WORD(lastTimeModified.day);
  DeNormalize_WORD(lastTimeModified.hour);
  DeNormalize_WORD(lastTimeModified.minute);
  DeNormalize_WORD(lastTimeModified.second);

  DeNormalize_WORD(lastTimeAccessed.year);
  DeNormalize_WORD(lastTimeAccessed.month);
  DeNormalize_WORD(lastTimeAccessed.day);
  DeNormalize_WORD(lastTimeAccessed.hour);
  DeNormalize_WORD(lastTimeAccessed.minute);
  DeNormalize_WORD(lastTimeAccessed.second);

  file.write(reinterpret_cast<char *>(&lastTimeModified), sizeof(DateTime));
  file.write(reinterpret_cast<char *>(&lastTimeAccessed), sizeof(DateTime));
}

void LayoutWriter_GDSIIBin::WriteSection_LIBNAME(Library *lib) {
  Record gdsiiRecord = { static_cast <int16_t>(sizeof(Record)) + static_cast<int16_t>(lib->name.length()) , rt_LIBNAME , 6 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // Write Data
  file.write(lib->name.data(), lib->name.length());
}

void LayoutWriter_GDSIIBin::WriteSection_UNITS(Library *lib) {
  Record gdsiiRecord = { sizeof(Record) + sizeof(Units) , rt_UNITS , 5};
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // Write Data
  Units units = lib->units;
  DeNormalize_DOUBLE(units.physical);
  DeNormalize_DOUBLE(units.user);

  file.write(reinterpret_cast<char *>(&units), sizeof(Units));
}

void LayoutWriter_GDSIIBin::WriteSection_ENDLIBRARY(Library *lib) {
  Record gdsiiRecord = { sizeof(Record) , rt_ENDLIB , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
}

void LayoutWriter_GDSIIBin::WriteSection_BEGINSTRUCTURE(Element *element) {
  Record gdsiiRecord = { sizeof(Record) + 2 * sizeof(DateTime) , rt_BGNSTR , 2 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // Write Data
  DateTime lastTimeModified = { 2001, 11, 11, 04, 43, 34 };
  DateTime lastTimeAccessed = { 2004,  8, 31, 13, 39, 37 };
  DeNormalize_WORD(lastTimeModified.year);
  DeNormalize_WORD(lastTimeModified.month);
  DeNormalize_WORD(lastTimeModified.day);
  DeNormalize_WORD(lastTimeModified.hour);
  DeNormalize_WORD(lastTimeModified.minute);
  DeNormalize_WORD(lastTimeModified.second);

  DeNormalize_WORD(lastTimeAccessed.year);
  DeNormalize_WORD(lastTimeAccessed.month);
  DeNormalize_WORD(lastTimeAccessed.day);
  DeNormalize_WORD(lastTimeAccessed.hour);
  DeNormalize_WORD(lastTimeAccessed.minute);
  DeNormalize_WORD(lastTimeAccessed.second);

  file.write(reinterpret_cast<char *>(&lastTimeModified), sizeof(DateTime));
  file.write(reinterpret_cast<char *>(&lastTimeAccessed), sizeof(DateTime));
}

void LayoutWriter_GDSIIBin::WriteSection_STRNAME(Element *element) {
  int actualNameLength = static_cast<int>(element->name.length());
  if(element->name.length() % 4 != 0)
    actualNameLength = ((static_cast<int>(element->name.length()) / 4) + 1) * 4;
  Record gdsiiRecord = { static_cast <int16_t>(sizeof(Record)) + static_cast<int16_t>(actualNameLength) , rt_STRNAME , 6 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // Write Data
  file.write(element->name.data(), element->name.length());
  if (element->name.length() % 4 != 0) {
    char zeroByte = 0;
    for (int i = 0; i < actualNameLength - element->name.length(); ++i)
      file.write(&zeroByte, 1);
  }
}

void LayoutWriter_GDSIIBin::WriteSection_ENDSTRUCTURE(Element *element) {
  Record gdsiiRecord = { sizeof(Record) , rt_ENDSTR , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
}

void LayoutWriter_GDSIIBin::WriteSection_BOUNDARY(GeometryItem_Boundary *boundary) {
  Record gdsiiRecord = { sizeof(Record) , rt_BOUNDARY , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // LAYER
  gdsiiRecord.recordType = rt_LAYER;
  gdsiiRecord.length = sizeof(Record) + sizeof(int16_t);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  int16_t layerNumber = boundary->layer;
  DeNormalize_WORD(layerNumber);
  file.write(reinterpret_cast<char *>(&layerNumber), sizeof(int16_t));
  // DATATYPE
  gdsiiRecord.recordType = rt_DATATYPE;
  gdsiiRecord.length = sizeof(Record) + sizeof(int16_t);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  int16_t dataType = boundary->dataType;
  DeNormalize_WORD(dataType);
  file.write(reinterpret_cast<char *>(&dataType), sizeof(int16_t));
  // XY
  gdsiiRecord.recordType = rt_XY;
  gdsiiRecord.length = sizeof(Record) + static_cast<int16_t>(boundary->coords.size()) * sizeof(Coord);
  gdsiiRecord.dataType = 3;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  for (size_t i = 0; i < boundary->coords.size(); ++i) {
    Coord coord = boundary->coords[i];
    DeNormalize_DWORD(coord.x);
    DeNormalize_DWORD(coord.y);
    file.write(reinterpret_cast<char *>(&coord), sizeof(Coord));
  }
  // ENDEL
  gdsiiRecord.recordType = rt_ENDEL;
  gdsiiRecord.length = sizeof(Record);
  gdsiiRecord.dataType = 0;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
}

void LayoutWriter_GDSIIBin::WriteSection_SREF(GeometryItem_StructureRef *reference) {
  Record gdsiiRecord = { sizeof(Record) , rt_SREF , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // SNAME
  gdsiiRecord.recordType = rt_SNAME;
  int actualNameLength = static_cast<int>(reference->name.length());
  if(reference->name.length() % 4 != 0)
    actualNameLength = static_cast<int>(((reference->name.length() / 4) + 1) * 4);
  gdsiiRecord.length = sizeof(Record) + static_cast<int16_t>(actualNameLength);
  gdsiiRecord.dataType = 6;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  file.write(reference->name.data(), reference->name.length());
  if (reference->name.length() % 4 != 0) {
    char zeroByte = 0;
    for (int i = 0; i < actualNameLength - reference->name.length(); ++i)
      file.write(&zeroByte, 1);
  }
  // XY
  gdsiiRecord.recordType = rt_XY;
  gdsiiRecord.length = sizeof(Record) + sizeof(Coord);
  gdsiiRecord.dataType = 3;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  Coord coord = reference->coords[0];
  DeNormalize_DWORD(coord.x);
  DeNormalize_DWORD(coord.y);
  file.write(reinterpret_cast<char *>(&coord), sizeof(Coord));
  // ENDEL
  gdsiiRecord.recordType = rt_ENDEL;
  gdsiiRecord.length = sizeof(Record);
  gdsiiRecord.dataType = 0;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
}

void LayoutWriter_GDSIIBin::WriteSection_PATH(GeometryItem_Path *path) {
  Record gdsiiRecord = { sizeof(Record) , rt_PATH , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // LAYER
  gdsiiRecord.recordType = rt_LAYER;
  gdsiiRecord.length = sizeof(Record) + sizeof(int16_t);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  int16_t layerNumber = path->layer;
  DeNormalize_WORD(layerNumber);
  file.write(reinterpret_cast<char *>(&layerNumber), sizeof(int16_t));
  // DATATYPE
  gdsiiRecord.recordType = rt_DATATYPE;
  gdsiiRecord.length = sizeof(Record) + sizeof(int16_t);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  int16_t dataType = path->dataType;
  DeNormalize_WORD(dataType);
  file.write(reinterpret_cast<char *>(&dataType), sizeof(int16_t));
  // DATATYPE
  gdsiiRecord.recordType = rt_PATHTYPE;
  gdsiiRecord.length = sizeof(Record) + sizeof(int16_t);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  int16_t pathType = path->pathType;
  DeNormalize_WORD(pathType);
  file.write(reinterpret_cast<char *>(&pathType), sizeof(int16_t));
  // WIDTH
  gdsiiRecord.recordType = rt_WIDTH;
  gdsiiRecord.length = sizeof(Record) + sizeof(int32_t);
  gdsiiRecord.dataType = 3;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  int32_t pathWidth = path->width;
  DeNormalize_DWORD(pathWidth);
  file.write(reinterpret_cast<char *>(&pathWidth), sizeof(int32_t));
  // XY
  gdsiiRecord.recordType = rt_XY;
  gdsiiRecord.length = sizeof(Record) + static_cast<int16_t>(path->coords.size()) * sizeof(Coord);
  gdsiiRecord.dataType = 3;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  for (size_t i = 0; i < path->coords.size(); ++i) {
    Coord coord = path->coords[i];
    DeNormalize_DWORD(coord.x);
    DeNormalize_DWORD(coord.y);
    file.write(reinterpret_cast<char *>(&coord), sizeof(Coord));
  }
  // ENDEL
  gdsiiRecord.recordType = rt_ENDEL;
  gdsiiRecord.length = sizeof(Record);
  gdsiiRecord.dataType = 0;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
}


