/*
 * LayoutReader_GDSIIascii.hpp
 *
 * Calma ASCII GDSII file format reader by Artem K. Efremov
 * 21.04.2023
 */
#pragma once

#include "Layout.hpp"
#include "LayoutReader.hpp"
#include "GDSIITypes.hpp"

class LayoutReader_GDSIIascii : public LayoutReader {
  Library      *activeLibrary;
  Element      *activeElement;
  Geometry     *activeGeometry;
public:
  LayoutReader_GDSIIascii();
public:
  bool IsMyFormat(const STR_CLASS &fName) final;
  bool Read(Layout *layout) final;
private:
	void ReadSection_HEADER();
	void ReadSection_BEGINLIBRARY();
	void ReadSection_LIBNAME();
	void ReadSection_UNITS();
	void ReadSection_ENDLIBRARY();
	void ReadSection_BEGINSTRUCTURE();
	void ReadSection_STRNAME();
	void ReadSection_ENDSTRUCTURE();
	void ReadSection_BOUNDARY();
	void ReadSection_PATH();
	void ReadSection_SREF();
	void ReadSection_TEXT();
	void ReadSection_LAYER();
	void ReadSection_DATATYPE();
	void ReadSection_WIDTH();
	void ReadSection_XY();
	void ReadSection_ENDELEMENT();
	void ReadSection_SNAME();
	void ReadSection_TEXTTYPE();
	void ReadSection_PRESENTATION();
	void ReadSection_STRING();
	void ReadSection_STRANS();
	void ReadSection_MAG();
	void ReadSection_PATHTYPE();
	void ReadSection_PROPATTR();
	void ReadSection_PROPVALUE();
	void ReadSection_BOX();
	void ReadSection_BOXTYPE();

	bool PostProcessLayout();

	bool ResolveStructureReference(Reference* p_reference);
	bool EnumerateLayers();
	void EvaluateBoundingBox();
};
