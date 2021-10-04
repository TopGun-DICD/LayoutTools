#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutData.hpp"

class LayoutWriter {
protected:
  LayoutData   *p_data;
  std::ofstream file;
public:
  LayoutWriter();
public:
  virtual bool Write(std::string fileName, LayoutData *layout) = 0;
};

class LayoutWriter_GDSIIBin : public LayoutWriter {
public:
  LayoutWriter_GDSIIBin();
public:
  bool Write(std::string fileName, LayoutData *layout) final;
private:
  void WriteSection_HEADER();

  void WriteSection_BEGINLIBRARY();
  void WriteSection_LIBNAME(Library *lib);
  void WriteSection_UNITS(Library *lib);
  void WriteSection_ENDLIBRARY(Library *lib);

  void WriteSection_BEGINSTRUCTURE(Element *element);
  void WriteSection_STRNAME(Element *element);

  void WriteSection_ENDSTRUCTURE(Element *element);

  void WriteSection_BOUNDARY(GeometryItem_Boundary *boundary);
  void WriteSection_SREF(GeometryItem_StructureRef *reference);
  void WriteSection_PATH(GeometryItem_Path *path);
};

LayoutWriter *GetWriter(const std::string &format);
void FreeWriter(LayoutWriter *ptr);