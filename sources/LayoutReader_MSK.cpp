/*
 * LayoutReader_MSK.cpp
 *
 * uWind (MicroWind) MSK file format reader by Mikhail S. Kotlyarov
 * 02.10.2021
 * updated 08.11.2022
 */

#include "LayoutReader_MSK.hpp"
#define _CRT_SECURE_NO_WARNINGS

#include <unordered_map>
#include <cstring>

static std::unordered_map <std::string, int16_t> g_layerMap = {
  {"TITLE",-6},
  {"BB",-5},
  {"VI",-4},
  {"NW",1},
  {"DN",16},
  {"DP",17},
  {"PO",13},
  {"CO",19},
  {"ME",23},
  {"M2",27},
  {"M3",34},
  {"M4",36},
  {"M5",53},
  {"M6",55},
};

constexpr int16_t g_undefinedValue = std::numeric_limits<int16_t>::min();

bool LayoutReader_MSK::IsMyFormat(const STR_CLASS &fName) {
  fileName = fName;

  if (fName.substr(fName.find_last_of(STR_VALUE(".")) + 1) != STR_VALUE("msk"))
    return false;

  file.open(fileName);
  if (!file.is_open())
    return false;

  std::string line;
  std::getline(file, line);
  if (line.length() < 7) { 
    file.close();
    return false;
  }

  if (line.substr(0, 7) != "VERSION") {
    file.close();
    return false;
  }

  file.close();
  return true;
}


int16_t LayoutReader_MSK::ConvertMskLayerNum(const std::string &LayerName)
{
  auto it = g_layerMap.find(LayerName);
  if (it == g_layerMap.end()) { return g_undefinedValue; }

  return it->second;
}


std::vector<Layer>::iterator LayoutReader_MSK::FindByLayerNum(std::vector <Layer> &Layers, int16_t LayerNum)
{
  for (std::vector<Layer>::iterator it = Layers.begin(); it != Layers.end(); it++)
  {
    if (it->layer == LayerNum)
    {
      return it;
    }
  }

  return Layers.end();
}

bool LayoutReader_MSK::Read(Layout *layout) 
{
  try {
    if (!layout) throw std::invalid_argument("Layout");

    file.open(std::string(fileName.begin(), fileName.end()));
    if (!file.is_open()) throw std::runtime_error("File was not opened");
    p_layout = layout;

    p_activeLibrary = new Library;
    p_activeElement = new Element;

    p_layout->fileName = this->fileName;
    p_activeElement->name = CONVERT_TO_STD_STRING(p_layout->fileName);
    p_activeLibrary->name = CONVERT_TO_STD_STRING(p_layout->fileName);

    //Переменная для хранения одной строки из файла
    std::string fileLine;
    while (std::getline(file, fileLine))
    {
      if (fileLine.find("BB") != std::string::npos) { ReadBoundingBox(fileLine); }
      if (fileLine.find("REC") != std::string::npos) { ReadSectionRectangle(fileLine); }
      if (fileLine.find("TITLE") != std::string::npos) { ReadTitle(fileLine); }
    }
    p_activeLibrary->elements.push_back(p_activeElement);
    p_layout->libraries.push_back(p_activeLibrary);

    layout->fileName = fileName;
    layout->fileFormat = FileFormat::MSK;

    layout->libraries[0]->elements[0]->minCoord = layout->libraries[0]->elements[0]->geometries[0]->minCoord;
    layout->libraries[0]->elements[0]->maxCoord = layout->libraries[0]->elements[0]->geometries[0]->maxCoord;

    for (size_t i = 1; i < layout->libraries[0]->elements[0]->geometries.size(); ++i) {
      if (layout->libraries[0]->elements[0]->minCoord.x > layout->libraries[0]->elements[0]->geometries[i]->minCoord.x)
        layout->libraries[0]->elements[0]->minCoord.x = layout->libraries[0]->elements[0]->geometries[i]->minCoord.x;
      if (layout->libraries[0]->elements[0]->minCoord.y > layout->libraries[0]->elements[0]->geometries[i]->minCoord.y)
        layout->libraries[0]->elements[0]->minCoord.y = layout->libraries[0]->elements[0]->geometries[i]->minCoord.y;
      if (layout->libraries[0]->elements[0]->maxCoord.x < layout->libraries[0]->elements[0]->geometries[i]->maxCoord.x)
        layout->libraries[0]->elements[0]->maxCoord.x = layout->libraries[0]->elements[0]->geometries[i]->maxCoord.x;
      if (layout->libraries[0]->elements[0]->maxCoord.y < layout->libraries[0]->elements[0]->geometries[i]->maxCoord.y)
        layout->libraries[0]->elements[0]->maxCoord.y = layout->libraries[0]->elements[0]->geometries[i]->maxCoord.y;
    }
  }
  catch (const std::exception &ex)
  {

    if (file.is_open()) { file.close(); }
    if (layout)
    {
      layout->fileFormat = FileFormat::undefined;
      if (p_activeElement)
      {
        delete p_activeElement;
        p_activeElement = nullptr;
      }
      if (p_activeLibrary)
      {
        delete p_activeLibrary;
        p_activeLibrary = nullptr;
      }

    }
    return false;
  }
  if (file.is_open()) { file.close(); }
  return true;
}


inline
bool
LayoutReader_MSK::ReadRecCoords(
  const std::string &Line,
  Coord &LeftBot,
  Coord &RightTop,
  std::string &LayerName)
{
  char layerNameCstr[8] = { '\0' };
  int32_t width = 0, height = 0;
  if (!sscanf_s(Line.c_str(), "REC(%d,%d,%d,%d,%s)", &LeftBot.x, &LeftBot.y, &width, &height, layerNameCstr, 8)) { return false; }

  LayerName = layerNameCstr;
  if (')' == LayerName[LayerName.length() - 1]) { LayerName.pop_back(); }
  //std::cout << layer_name << std::endl;
  RightTop.x = LeftBot.x + width;
  RightTop.y = LeftBot.y + height;
  return true;
}


void
LayoutReader_MSK::FillBox(
  Geometry* Box2Fill,
  const Coord &LeftBot,
  const Coord &RightTop,
  uint16_t LayerNum)
{
  Coord currCoord;
  int32_t dx = calcDelta(LeftBot.x, RightTop.x);
  int32_t dy = calcDelta(LeftBot.y, RightTop.y);

  //Left top
  currCoord.x = RightTop.x - dx;
  currCoord.y = RightTop.y;
  Box2Fill->coords.push_back(currCoord);

  //Right top
  Box2Fill->coords.push_back(RightTop);

  //Right bot
  currCoord.x = RightTop.x;
  currCoord.y = RightTop.y - dy;
  Box2Fill->coords.push_back(currCoord);

  //Left bot
  currCoord.x = RightTop.x - dx;
  currCoord.y = RightTop.y - dy;
  Box2Fill->coords.push_back(currCoord);

  //Left top
  currCoord.x = RightTop.x - dx;
  currCoord.y = RightTop.y;
  Box2Fill->coords.push_back(currCoord);

  Box2Fill->layer = LayerNum;

  Box2Fill->minCoord = Box2Fill->maxCoord = Box2Fill->coords[0];
  for (size_t i = 1; i < Box2Fill->coords.size(); ++i) {
    if (Box2Fill->minCoord.x > Box2Fill->coords[i].x)
      Box2Fill->minCoord.x = Box2Fill->coords[i].x;
    if (Box2Fill->minCoord.y > Box2Fill->coords[i].y)
      Box2Fill->minCoord.y = Box2Fill->coords[i].y;
    if (Box2Fill->maxCoord.x < Box2Fill->coords[i].x)
      Box2Fill->maxCoord.x = Box2Fill->coords[i].x;
    if (Box2Fill->maxCoord.y < Box2Fill->coords[i].y)
      Box2Fill->maxCoord.y = Box2Fill->coords[i].y;
  }
}


void
LayoutReader_MSK::ReadSectionRectangle(
  const std::string &FileLine)
{
  Geometry* currBox = new Rectangle;
  try {
    Coord leftBot = {};
    Coord rightTop = {};
    std::string layerName;
    if (!ReadRecCoords(FileLine, leftBot, rightTop, layerName)) { throw std::runtime_error("Coordinates was not read"); }

    const int16_t layerNum = ConvertMskLayerNum(layerName);
    if (layerNum == g_undefinedValue) { throw std::runtime_error("File contains invalid layer!"); }

    FillBox(currBox, leftBot, rightTop, layerNum);

    auto it = FindByLayerNum(p_activeLibrary->layers, layerNum);
    if (p_activeLibrary->layers.end() == it)
    {
      Layer tmpLayer;
      tmpLayer.layer = currBox->layer;
      tmpLayer.dataType = 0;
      tmpLayer.name = layerName;
      tmpLayer.geometries.push_back(currBox);
      p_activeLibrary->layers.push_back(tmpLayer);
    }
    else
    {
      it->geometries.push_back(currBox);
    }

    p_activeElement->geometries.push_back(currBox);
  }
  catch (const std::exception &ex)
  {
    if (currBox)
    {
      delete currBox;
      currBox = nullptr;
    }
  }
}


void
LayoutReader_MSK::ReadBoundingBox(
  const std::string &FileLine)
{
  Geometry* boundingBox = new Rectangle;
  try {
    Coord leftBot;
    Coord rightTop;
    if (!sscanf_s(FileLine.c_str(), "BB(%d,%d,%d,%d)", &leftBot.x, &leftBot.y, &rightTop.x, &rightTop.y)) { throw std::runtime_error("Coordinates was not read"); }
    Layer boundingBoxLayer;
    int16_t layerNum = g_layerMap.find("BB")->second;
    boundingBoxLayer.layer = layerNum;
    boundingBoxLayer.dataType = 0;
    boundingBoxLayer.name = "BB";

    FillBox(boundingBox, leftBot, rightTop, layerNum);

    boundingBoxLayer.geometries.push_back(boundingBox);
    p_activeLibrary->layers.push_back(boundingBoxLayer);
    p_activeElement->geometries.push_back(boundingBox);
  }
  catch (std::exception &ex)
  {
    if (boundingBox)
    {
      delete boundingBox;
      boundingBox = nullptr;
    }
  }
}


void
LayoutReader_MSK::ReadTitle(
  const std::string &FileLine)
{
  Geometry* text = new Text;
  Text* p_text = static_cast<Text*>(text);
  try
  {
    char buf[64] = { '\0' };
    Coord leftBot;

    if (!sscanf_s(FileLine.c_str(), "TITLE %d %d  #%s", &leftBot.x, &leftBot.y, buf, 64)) { throw std::runtime_error("Title was not read"); }

    p_text->coords.push_back(leftBot);
    p_text->layer = g_layerMap.find("TITLE")->second;
    p_text->minCoord = p_text->maxCoord = leftBot;
    p_text->width = static_cast<int32_t>(strlen(buf));
    p_text->stringValue = buf;
  }
  catch (std::exception &ex)
  {
    if (text)
    {
      delete text;
      text = nullptr;
    }
  }
}


inline
int32_t
LayoutReader_MSK::calcDelta(
  int32_t first,
  int32_t second)
{
  return second - first;
}

