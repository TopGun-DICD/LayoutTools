/*
 * LayoutReader.hpp
 *
 * Layout formats implementation:
 * GDSII Binary - Dmitry A. Bulakh
 * MSK          - Mikhail S. Kotlyarov 
 */
#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>

#include "LayoutData.hpp"
#include "GDSIITypes.hpp"

class LayoutReader {
protected:
  std::string   fileName;
  LayoutData   *p_data;
  std::ifstream file;
public:
  LayoutReader();
public:
  virtual bool IsMyFormat(const std::string &fName) = 0;
  virtual bool Read(LayoutData *layout) = 0;
};

class LayoutReader_GDSIIBin : public LayoutReader {
  Library      *p_activeLibrary;
  Element      *p_activeElement;
  GeometryItem *p_activeItem;
public:
  LayoutReader_GDSIIBin();
public:
  bool IsMyFormat(const std::string &fName) final;
  bool Read(LayoutData *layout) final;
private:
  void ReadSection_HEADER(Record &_record);
  void ReadSection_BEGINLIBRARY(Record &_record);
  void ReadSection_LIBNAME(Record &_record);
  void ReadSection_UNITS(Record &_record);
  void ReadSection_ENDLIBRARY(Record &_record);
  void ReadSection_BEGINSTRUCTURE(Record &_record);
  void ReadSection_STRNAME(Record &_record);
  void ReadSection_ENDSTRUCTURE(Record &_record);
  void ReadSection_BOUNDARY(Record &_record);
  void ReadSection_PATH(Record &_record);
  void ReadSection_SREF(Record &_record);
  //void ReadSection_AREF(Record &_record);
  void ReadSection_TEXT(Record &_record);
  void ReadSection_LAYER(Record &_record);
  void ReadSection_DATATYPE(Record &_record);
  void ReadSection_WIDTH(Record &_record);
  void ReadSection_XY(Record &_record);
  void ReadSection_ENDELEMENT(Record &_record);
  void ReadSection_SNAME(Record &_record);
  //void ReadSection_COLROW(Record &_record);
  //void ReadSection_TEXTNODE(Record &_record);
  //void ReadSection_NODE(Record &_record);
  void ReadSection_TEXTTYPE(Record &_record);
  void ReadSection_PRESENTATION(Record &_record);
  // UNUSED
  void ReadSection_STRING(Record &_record);
  void ReadSection_STRANS(Record &_record);
  void ReadSection_MAG(Record &_record);
  //void ReadSection_ANGLE(Record &_record);
  //void ReadSection_LINKTYPE(Record &_record);
  //void ReadSection_LINKKEYS(Record &_record);
  //void ReadSection_REFLIBS(Record &_record);
  //void ReadSection_FONTS(Record &_record);
  void ReadSection_PATHTYPE(Record &_record);
  //void ReadSection_GENERATIONS(Record &_record);
  //void ReadSection_ATTRTABLE(Record &_record);
  //void ReadSection_STYPTABLE(Record &_record);
  //void ReadSection_STRTYPE(Record &_record);
  //void ReadSection_ELFLAGS(Record &_record);
  //void ReadSection_ELKEY(Record &_record);
  // UNUSED
  // UNUSED
  //void ReadSection_NODETYPE(Record &_record);
  void ReadSection_PROPATTR(Record &_record);
  void ReadSection_PROPVALUE(Record &_record);
  void ReadSection_BOX(Record &_record);
  void ReadSection_BOXTYPE(Record &_record);
  //void ReadSection_PLEX(Record &_record);
  //void ReadSection_BGNEXTN(Record &_record);
  //void ReadSection_ENDTEXTN(Record &_record);
  //void ReadSection_TAPENUM(Record &_record);
  //void ReadSection_TAPECODE(Record &_record);
  //void ReadSection_STRCLASS(Record &_record);
  //void ReadSection_RESERVED(Record &_record);
  //void ReadSection_FORMAT(Record &_record);
  //void ReadSection_MASK(Record &_record);
  //void ReadSection_ENDMASK(Record &_record);
  //void ReadSection_LIBDIRSIZE(Record &_record);
  //void ReadSection_SRFNAME(Record &_record);
  //void ReadSection_LIBSECUR(Record &_record);

  bool ResolveReferences();
};

class LayoutReader_MSK:public AbstractLayoutReader
{
private:
	Library*			p_active_library;
	Element*			p_active_element;
	GeometryItem*       p_active_geometry_item;

public:
	LayoutReader_MSK() :p_active_library(nullptr),p_active_element(nullptr),p_active_geometry_item(nullptr) {}

	bool             IsMyFormat(const std::string& fName) override final;
	bool             Read(LayoutData* layout) override final;
private:
	inline bool      read_Rectangle_coords(const std::string& line, Coord& left_bot, Coord& right_top, std::string& layer_name);
	void		     fill_GeometryItem_box(GeometryItem* filling_box, const Coord& right_top, const Coord& left_bot, const uint16_t layer_num);
	inline int32_t   calculate_delta(const int32_t first, const int32_t second);
	int16_t			 calculate_MSK_layer_num(const std::string& layer_name);
	inline int32_t   find_layer_num(const std::vector <Layer>& all_layers, const uint16_t layer_num);
	std::string      receive_element_name();

};

LayoutReader *GetReader(const std::string &fName);
void FreeReader(LayoutReader *ptr);
