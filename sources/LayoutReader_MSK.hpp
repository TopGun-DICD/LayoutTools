/*
 * LayoutReader_MSK.hpp
 *
 * uWind (MicroWind) MSK file format reader by Mikhail S. Kotlyarov
 * updated 08.11.2022
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "LayoutReader.hpp"
#include "Layout.hpp"

class LayoutReader_MSK:public LayoutReader
{
private:
  Library  *p_activeLibrary;
  Element  *p_activeElement;
  Geometry *p_active_geometry_item;

public:
  LayoutReader_MSK() : p_activeLibrary(nullptr), p_activeElement(nullptr), p_active_geometry_item(nullptr) {}

  bool            IsMyFormat(const STR_CLASS &fName) override final;
  bool            Read(Layout *layout) override final;
private:

  void ReadSectionRectangle(const std::string &FileLine);
  void ReadBoundingBox(const std::string &FileLine);
  void ReadTitle(const std::string &FileLine);

  inline bool     ReadRecCoords(const std::string &line, Coord &left_bot, Coord &right_top, std::string &layer_name);
  void            FillBox(Geometry* filling_box, const Coord &right_top, const Coord &left_bot, uint16_t layer_num);
  std::string     GetElemName();

  int16_t         ConvertMskLayerNum(const std::string &layer_name);
  std::vector<Layer>::iterator FindByLayerNum(std::vector <Layer> &all_layers, int16_t layer_num);

  inline int32_t  calcDelta(int32_t first, int32_t second);
};
