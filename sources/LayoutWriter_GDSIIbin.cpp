#include "LayoutWriter.hpp"
#include "HelperFunctions.hpp"

#include <ctime>
#include "GDSIITypes.hpp"

GDSIIBinaryWriter::GDSIIBinaryWriter() {

}

bool GDSIIBinaryWriter::Write(std::string fileName, LayoutData *layout) {
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
        //if (j == 1 && k == 16)
        //  break;
        switch (layout->libraries[i]->elements[j]->items[k]->type) {
          case it_boundary:
            WriteSection_BOUNDARY(reinterpret_cast<GeometryItem_Boundary *>(layout->libraries[i]->elements[j]->items[k]));
            break;
          case it_structRef:
            WriteSection_SREF(reinterpret_cast<GeometryItem_StructureRef *>(layout->libraries[i]->elements[j]->items[k]));
            break;
          case it_path:
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

void GDSIIBinaryWriter::WriteSection_HEADER() {
  Record gdsiiRecord = { sizeof(Record) + sizeof(__int16) , rt_HEADER , 2 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record)); 
  // Write Data
  __int16 versionNumber = 600;
  DeNormalize_WORD(versionNumber);
  file.write(reinterpret_cast<char *>(&versionNumber), sizeof(__int16));
}

void GDSIIBinaryWriter::WriteSection_BEGINLIBRARY() {
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

void GDSIIBinaryWriter::WriteSection_LIBNAME(Library *lib) {
  Record gdsiiRecord = { static_cast < __int16>(sizeof(Record)) + static_cast<__int16>(lib->name.length()) , rt_LIBNAME , 6 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // Write Data
  file.write(lib->name.data(), lib->name.length());
}

void GDSIIBinaryWriter::WriteSection_UNITS(Library *lib) {
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

void GDSIIBinaryWriter::WriteSection_ENDLIBRARY(Library *lib) {
  Record gdsiiRecord = { sizeof(Record) , rt_ENDLIB , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
}

void GDSIIBinaryWriter::WriteSection_BEGINSTRUCTURE(Element *element) {
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

void GDSIIBinaryWriter::WriteSection_STRNAME(Element *element) {
  int actualNameLength = static_cast<int>(element->name.length());
  if(element->name.length() % 4 != 0)
    actualNameLength = ((static_cast<int>(element->name.length()) / 4) + 1) * 4;
  Record gdsiiRecord = { static_cast < __int16>(sizeof(Record)) + static_cast<__int16>(actualNameLength) , rt_STRNAME , 6 };
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

void GDSIIBinaryWriter::WriteSection_ENDSTRUCTURE(Element *element) {
  Record gdsiiRecord = { sizeof(Record) , rt_ENDSTR , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
}

void GDSIIBinaryWriter::WriteSection_BOUNDARY(GeometryItem_Boundary *boundary) {
  Record gdsiiRecord = { sizeof(Record) , rt_BOUNDARY , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // LAYER
  gdsiiRecord.recordType = rt_LAYER;
  gdsiiRecord.length = sizeof(Record) + sizeof(__int16);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  __int16 layerNumber = boundary->layer;
  DeNormalize_WORD(layerNumber);
  file.write(reinterpret_cast<char *>(&layerNumber), sizeof(__int16));
  // DATATYPE
  gdsiiRecord.recordType = rt_DATATYPE;
  gdsiiRecord.length = sizeof(Record) + sizeof(__int16);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  __int16 dataType = boundary->dataType;
  DeNormalize_WORD(dataType);
  file.write(reinterpret_cast<char *>(&dataType), sizeof(__int16));
  // XY
  gdsiiRecord.recordType = rt_XY;
  gdsiiRecord.length = sizeof(Record) + static_cast<__int16>(boundary->coords.size()) * sizeof(Coord);
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

void GDSIIBinaryWriter::WriteSection_SREF(GeometryItem_StructureRef *reference) {
  Record gdsiiRecord = { sizeof(Record) , rt_SREF , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // SNAME
  gdsiiRecord.recordType = rt_SNAME;
  int actualNameLength = static_cast<int>(reference->name.length());
  if(reference->name.length() % 4 != 0)
    actualNameLength = static_cast<int>(((reference->name.length() / 4) + 1) * 4);
  gdsiiRecord.length = sizeof(Record) + static_cast<__int16>(actualNameLength);
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

void GDSIIBinaryWriter::WriteSection_PATH(GeometryItem_Path *path) {
  Record gdsiiRecord = { sizeof(Record) , rt_PATH , 0 };
  // Write Header
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  // LAYER
  gdsiiRecord.recordType = rt_LAYER;
  gdsiiRecord.length = sizeof(Record) + sizeof(__int16);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  __int16 layerNumber = path->layer;
  DeNormalize_WORD(layerNumber);
  file.write(reinterpret_cast<char *>(&layerNumber), sizeof(__int16));
  // DATATYPE
  gdsiiRecord.recordType = rt_DATATYPE;
  gdsiiRecord.length = sizeof(Record) + sizeof(__int16);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  __int16 dataType = path->dataType;
  DeNormalize_WORD(dataType);
  file.write(reinterpret_cast<char *>(&dataType), sizeof(__int16));
  // DATATYPE
  gdsiiRecord.recordType = rt_PATHTYPE;
  gdsiiRecord.length = sizeof(Record) + sizeof(__int16);
  gdsiiRecord.dataType = 2;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  __int16 pathType = path->pathType;
  DeNormalize_WORD(pathType);
  file.write(reinterpret_cast<char *>(&pathType), sizeof(__int16));
  // WIDTH
  gdsiiRecord.recordType = rt_WIDTH;
  gdsiiRecord.length = sizeof(Record) + sizeof(__int32);
  gdsiiRecord.dataType = 3;
  DeNormalize_WORD(gdsiiRecord.length);
  file.write(reinterpret_cast<char *>(&gdsiiRecord), sizeof(Record));
  __int32 pathWidth = path->width;
  DeNormalize_DWORD(pathWidth);
  file.write(reinterpret_cast<char *>(&pathWidth), sizeof(__int32));
  // XY
  gdsiiRecord.recordType = rt_XY;
  gdsiiRecord.length = sizeof(Record) + static_cast<__int16>(path->coords.size()) * sizeof(Coord);
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

