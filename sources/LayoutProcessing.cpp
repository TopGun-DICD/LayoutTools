#include "LayoutProcessing.hpp"
#include "LayoutReader.hpp"

LayoutData* ReadLayoutFromFile(std::wstring fileName) {
  LayoutReader* p_reader = GetReader(fileName);

  if (!p_reader)
    return nullptr;

  LayoutData* p_layout = new LayoutData;
  p_layout->fileFormat = LayoutFileFormat::undefined;

  if (!p_reader->Read(p_layout)) {
    FreeReader(p_reader);
    delete p_layout;
    return nullptr;
  }
  FreeReader(p_reader);

  p_layout->fileName = fileName;
  return p_layout;
}

void ReadLayoutFromFile(std::wstring fileName, LayoutData* layout) {
  LayoutReader* p_reader = GetReader(fileName);

  if (!p_reader)
    return;

  layout->fileFormat = LayoutFileFormat::undefined;

  if (!p_reader->Read(layout)) {
    FreeReader(p_reader);
    return;
  }
  FreeReader(p_reader);

  layout->fileName = fileName;
}

bool CopyLayout(const LayoutData* src, LayoutData* dst) {
  if (!src)
    return false;
  if (!dst)
    return false;

  Path       *p_path    = nullptr;
  Rectangle  *p_rect    = nullptr;
  Polygon    *p_polygon = nullptr;
  Text       *p_text    = nullptr;
  Reference  *p_ref     = nullptr;

  for (size_t i = 0; i < src->libraries.size(); ++i) {
    dst->libraries.push_back(new Library);
    dst->libraries[i]->name = src->libraries[i]->name;
    dst->libraries[i]->units = src->libraries[i]->units;

    for (size_t j = 0; j < src->libraries[i]->elements.size(); ++j) {
      dst->libraries[i]->elements.push_back(new Element);
      dst->libraries[i]->elements[j]->name = src->libraries[i]->elements[j]->name;

      for (size_t k = 0; k < src->libraries[i]->elements[j]->geometries.size(); ++k) {
        switch (src->libraries[i]->elements[j]->geometries[k]->type) {
          case GeometryType::path:
            p_path = new Path;
            dst->libraries[i]->elements[j]->geometries.push_back(p_path);
            p_path->layer = src->libraries[i]->elements[j]->geometries[k]->layer;
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->properties.size(); ++l)
              p_path->properties.push_back(src->libraries[i]->elements[j]->geometries[k]->properties[l]);
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->coords.size(); ++l)
              p_path->coords.push_back(src->libraries[i]->elements[j]->geometries[k]->coords[l]);
            p_path->dataType = static_cast<Path*>(src->libraries[i]->elements[j]->geometries[k])->dataType;
            p_path->pathType = static_cast<Path*>(src->libraries[i]->elements[j]->geometries[k])->pathType;
            p_path->width = static_cast<Path*>(src->libraries[i]->elements[j]->geometries[k])->width;
            break;
          case GeometryType::rectangle:
            p_rect = new Rectangle;
            dst->libraries[i]->elements[j]->geometries.push_back(p_rect);
            p_rect->layer = src->libraries[i]->elements[j]->geometries[k]->layer;
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->properties.size(); ++l)
              p_rect->properties.push_back(src->libraries[i]->elements[j]->geometries[k]->properties[l]);
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->coords.size(); ++l)
              p_rect->coords.push_back(src->libraries[i]->elements[j]->geometries[k]->coords[l]);
            p_rect->rectType = static_cast<Rectangle*>(src->libraries[i]->elements[j]->geometries[k])->rectType;
            break;
          case GeometryType::polygon:
            p_polygon = new Polygon;
            dst->libraries[i]->elements[j]->geometries.push_back(p_polygon);
            p_polygon->layer = src->libraries[i]->elements[j]->geometries[k]->layer;
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->properties.size(); ++l)
              p_polygon->properties.push_back(src->libraries[i]->elements[j]->geometries[k]->properties[l]);
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->coords.size(); ++l)
              p_polygon->coords.push_back(src->libraries[i]->elements[j]->geometries[k]->coords[l]);
            p_polygon->dataType = static_cast<Polygon*>(src->libraries[i]->elements[j]->geometries[k])->dataType;
            break;
          case GeometryType::text:
            p_text = new Text;
            dst->libraries[i]->elements[j]->geometries.push_back(p_text);
            p_text->type = GeometryType::text;
            p_text->layer = src->libraries[i]->elements[j]->geometries[k]->layer;
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->properties.size(); ++l)
              p_text->properties.push_back(src->libraries[i]->elements[j]->geometries[k]->properties[l]);
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->coords.size(); ++l)
              p_text->coords.push_back(src->libraries[i]->elements[j]->geometries[k]->coords[l]);
            p_text->textType = static_cast<Text*>(src->libraries[i]->elements[j]->geometries[k])->textType;
            p_text->pathType = static_cast<Text*>(src->libraries[i]->elements[j]->geometries[k])->pathType;
            p_text->width = static_cast<Text*>(src->libraries[i]->elements[j]->geometries[k])->width;
            p_text->flagsPresentation = static_cast<Text*>(src->libraries[i]->elements[j]->geometries[k])->flagsPresentation;
            p_text->flagsTransformation = static_cast<Text*>(src->libraries[i]->elements[j]->geometries[k])->flagsTransformation;
            p_text->magnification = static_cast<Text*>(src->libraries[i]->elements[j]->geometries[k])->magnification;
            p_text->stringValue = static_cast<Text*>(src->libraries[i]->elements[j]->geometries[k])->stringValue;
            break;
          case GeometryType::reference:
            p_ref = new Reference;
            dst->libraries[i]->elements[j]->geometries.push_back(p_ref);
            p_ref->type = GeometryType::reference;
            p_ref->layer = src->libraries[i]->elements[j]->geometries[k]->layer;
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->properties.size(); ++l)
              p_ref->properties.push_back(src->libraries[i]->elements[j]->geometries[k]->properties[l]);
            for (size_t l = 0; l < src->libraries[i]->elements[j]->geometries[k]->coords.size(); ++l)
              p_ref->coords.push_back(src->libraries[i]->elements[j]->geometries[k]->coords[l]);
            p_ref->name = static_cast<Reference*>(src->libraries[i]->elements[j]->geometries[k])->name;
            //p_ref->pElement = !!! //static_cast<Reference*>(src->libraries[i]->elements[j]->geometries[k])->referenceTo;
            p_ref->transformationFlags = static_cast<Reference*>(src->libraries[i]->elements[j]->geometries[k])->transformationFlags;
            p_ref->magnification = static_cast<Reference*>(src->libraries[i]->elements[j]->geometries[k])->magnification;
            break;
        }
      } // for k : geometries
    } // for j : elements
  } // for i : libraries

  //TODO: Fill layers information (correctly, with hierarchy instances!)
  return true;
}