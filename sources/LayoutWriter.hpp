#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutData.hpp"

class AbstractLayoutWriter {
protected:
  LayoutData   *p_data;
  std::ofstream file;
public:
  AbstractLayoutWriter();
public:
  virtual bool Write(std::string fileName, LayoutData *layout) = 0;
};

class GDSIIBinaryWriter : public AbstractLayoutWriter {
public:
  GDSIIBinaryWriter();
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

AbstractLayoutWriter *GetWriter(const std::string &format);
void FreeWriter(AbstractLayoutWriter *ptr);