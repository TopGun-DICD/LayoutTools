#pragma once

#include <string>
#include <vector>

struct Units {
  double  user,
    physical;
};

struct Coord {
  __int32 x,
          y;
};

struct Property {
  __int16     index;
  std::string value;
};

enum ItemType {
  it_undefined = 0,
  it_boundary,
  it_path,
  it_text,
  it_box,
  it_structRef,
};

enum DataType {
  dt_noData = 0,
  dt_bitArray,
  dt_WORD,
  dt_DWORD,
  dt_REAL,
  dt_DOUBLE,
  dt_ASCIISTRING,
};

struct GeometryItem {
  ItemType                    type;
  __int16                     layer;
  std::vector<Property>       properties;
  std::vector<Coord>          coords;
public:
  GeometryItem(ItemType t) : type(t), layer(-1) {}
};

struct GeometryItem_Boundary : public GeometryItem {
  __int16                     dataType;
public:
  GeometryItem_Boundary() : GeometryItem(it_boundary), dataType(0) {}
};

struct GeometryItem_Path : public GeometryItem {
  __int16                     dataType,
    pathType;
  __int32                     width;
public:
  GeometryItem_Path() : GeometryItem(it_path), dataType(0), pathType(0), width(0) {}
};

struct GeometryItem_Text : public GeometryItem {
  __int16                     textType,
    flagsPresentation,
    pathType,
    flagsTransformation;
  double                      magnification;
  __int32                     width;
  std::string                 stringValue;
public:
  GeometryItem_Text() : GeometryItem(it_text), textType(0), flagsPresentation(0), pathType(0), flagsTransformation(0), magnification(1.0), width(0) {}
};

struct GeometryItem_Box : public GeometryItem {
  __int16                     boxType;
public:
  GeometryItem_Box() : GeometryItem(it_box), boxType(0) {}
};

struct Element;

struct GeometryItem_StructureRef : public GeometryItem {
  std::string                 name;
  Element                    *pReference;
  __int16                     transformationFlags;
  double                      magnification;
public:
  GeometryItem_StructureRef() : GeometryItem(it_structRef), name(""), pReference(nullptr), transformationFlags(0), magnification(1.0) {}
};







struct Element {
  std::string                 name;
  std::vector<GeometryItem *> items;
public:
  ~Element() {
    for (size_t i = 0; i < items.size(); ++i) {
      delete items[i];
      items[i] = nullptr;
    }
    items.clear();
  }
};

struct LayerInfo {
  __int16                     layer;
  std::string                 name;
  std::vector<GeometryItem *> items;
};

struct Library {
  std::string                 name;
  Units                       units;
  std::vector<Element *>      elements;
  std::vector<LayerInfo>      layers;
public:
  ~Library() {
    for (size_t i = 0; i < elements.size(); ++i) {
      delete elements[i];
      elements[i] = nullptr;
    }
    elements.clear();
    layers.clear();
  }
};

struct LayoutData {
  std::string                 fileName;
  std::vector<Library *>      libraries;
public:
  ~LayoutData() {
    for (size_t i = 0; i < libraries.size(); ++i) {
      delete libraries[i];
      libraries[i] = nullptr;
    }
    libraries.clear();
  }
};
