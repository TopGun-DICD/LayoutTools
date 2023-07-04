/*
 * LayoutWriter_GDSIIascii.hpp
 *
 * Calma binary GDSII file format writer by Artem K. Efremov
 * 03.07.2023
 */
#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "LayoutWriter.hpp"
#include "Layout.hpp"

class LayoutWriter_GDSIIascii : public LayoutWriter {
public:
  LayoutWriter_GDSIIascii();
public:
  bool Write(const STR_CLASS &fileName, Layout *layout) final;
private:
	void WriteSection_HEADER();

	void WriteSection_BEGINLIBRARY();
	void WriteSection_LIBNAME(Library* lib);
	void WriteSection_UNITS(Library* lib);
	void WriteSection_ENDLIBRARY(Library* lib);

	void WriteSection_BEGINSTRUCTURE(Element* element);
	void WriteSection_STRNAME(Element* element);

	void WriteSection_ENDSTRUCTURE(Element* element);

	void WriteSection_BOUNDARY(Polygon* polygon);
	void WriteSection_BOX(Rectangle* rectangle);
	void WriteSection_SREF(Reference* reference);
	void WriteSection_PATH(Path* path);
};
