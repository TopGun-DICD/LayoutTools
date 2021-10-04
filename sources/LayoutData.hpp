#pragma once

#include <string>
#include <vector>

struct Units {
  double  user,
          physical;
};

struct Coord {
  int32_t x,
          y;
};

struct Property {
  int16_t     index;
  std::string value;
};

enum class ItemType {
  undefined = 0,
  boundary,
  path,
  text,
  box,
  reference,
};

enum class DataType {
  noData = 0,
  bitArray,
  WORD,
  DWORD,
  REAL,
  DOUBLE,
  ASCIISTRING,
};

struct GeometryItem {
  ItemType                    type;
  int16_t                     layer;
  std::vector<Property>       properties;
  std::vector<Coord>          coords;
public:
  GeometryItem(ItemType t) : type(t), layer(-1) {}
};

struct GeometryItem_Boundary : public GeometryItem {
  int16_t                     dataType;
public:
  GeometryItem_Boundary() : GeometryItem(ItemType::boundary), dataType(0) {}
};

struct GeometryItem_Path : public GeometryItem {
  int16_t                     dataType,
                              pathType;
  int32_t                     width;
public:
  GeometryItem_Path() : GeometryItem(ItemType::path), dataType(0), pathType(0), width(0) {}
};

struct GeometryItem_Text : public GeometryItem {
  int16_t                     textType,
                              flagsPresentation,
                              pathType,
                              flagsTransformation;
  double                      magnification;
  int32_t                     width;
  std::string                 stringValue;
public:
  GeometryItem_Text() : GeometryItem(ItemType::text), textType(0), flagsPresentation(0), pathType(0), flagsTransformation(0), magnification(1.0), width(0) {}
};

struct GeometryItem_Box : public GeometryItem {
  int16_t                     boxType;
public:
  GeometryItem_Box() : GeometryItem(ItemType::box), boxType(0) {}
};

struct Element;

struct GeometryItem_StructureRef : public GeometryItem {
  std::string                 name;
  Element                    *pReference;
  int32_t                     transformationFlags;
  double                      magnification;
public:
  GeometryItem_StructureRef() : GeometryItem(ItemType::reference), name(""), pReference(nullptr), transformationFlags(0), magnification(1.0) {}
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

struct Layer {
  int16_t                     layer;
  std::string                 name;
  std::vector<GeometryItem *> items;
};

struct Library {
  std::string                 name;
  Units                       units;
  std::vector<Element *>      elements;
  std::vector<Layer>          layers;
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
