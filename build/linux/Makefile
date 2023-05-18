SRC=../../sources
BIN=../../bin
#CXX=g++ -Wall -std=c++0x
CXX=g++ -Wall -std=c++11

all:		main

main:				GDSIIReaderASCII.o GDSIIReaderBIN.o GDSIIWriterASCII.o GDSIIWriterBIN.o \
					LayoutProcessing.o LayoutReader.o LayoutWriter.o GDSIIHelper.o ${SRC}/main.cpp
					@echo Building all together
					${CXX} \
					GDSIIReaderASCII.o GDSIIReaderBIN.o LayoutProcessing.o LayoutReader.o LayoutWriter.o GDSIIHelper.o \
					${SRC}/main.cpp -o ${BIN}/LayoutTools

# All for GDSII format 
GDSIIHelper.o:		${SRC}/GDSIIHelperFunctions.hpp ${SRC}/GDSIIHelperFunctions.cpp
					@echo Building GDSII Helper
					${CXX} -c ${SRC}/GDSIIHelperFunctions.cpp -o GDSIIHelper.o

GDSIIReaderASCII.o:	${SRC}/GDSIITypes.hpp ${SRC}/GDSIIHelperFunctions.hpp \
					${SRC}/LayoutReader_GDSIIascii.hpp ${SRC}/LayoutReader_GDSIIascii.cpp
					@echo Building GDSII-ASCII reader
					${CXX} -c ${SRC}/LayoutReader_GDSIIascii.cpp -o GDSIIReaderASCII.o

GDSIIWriterASCII.o:	${SRC}/GDSIITypes.hpp ${SRC}/GDSIIHelperFunctions.hpp \
					${SRC}/LayoutWriter_GDSIIascii.hpp ${SRC}/LayoutWriter_GDSIIascii.cpp
					@echo Building GDSII-ASCII writer
					${CXX} -c ${SRC}/LayoutWriter_GDSIIascii.cpp -o GDSIIWriterASCII.o

GDSIIReaderBIN.o:	${SRC}/GDSIITypes.hpp ${SRC}/GDSIIHelperFunctions.hpp \
					${SRC}/LayoutReader_GDSIIbin.hpp ${SRC}/LayoutReader_GDSIIbin.cpp
					@echo Building GDSII-bin reader
					${CXX} -c ${SRC}/LayoutReader_GDSIIbin.cpp -o GDSIIReaderBIN.o

GDSIIWriterBIN.o:	${SRC}/GDSIITypes.hpp ${SRC}/GDSIIHelperFunctions.hpp \
					${SRC}/LayoutWriter_GDSIIbin.hpp ${SRC}/LayoutWriter_GDSIIbin.cpp
					@echo Building GDSII-bin writer
					${CXX} -c ${SRC}/LayoutWriter_GDSIIbin.cpp -o GDSIIWriterBIN.o

# All for LayoutTools in general

LayoutProcessing.o:	${SRC}/LayoutProcessing.hpp ${SRC}/LayoutProcessing.cpp
					@echo Building layout processing functions
					${CXX} -c ${SRC}/LayoutProcessing.cpp -o LayoutProcessing.o

LayoutReader.o:		${SRC}/LayoutReader.hpp ${SRC}/LayoutReader.cpp
					@echo Building interface for layout reader
					${CXX} -c ${SRC}/LayoutReader.cpp -o LayoutReader.o

LayoutWriter.o:		${SRC}/LayoutWriter.hpp ${SRC}/LayoutWriter.cpp
					@echo Building interface for layout writer
					${CXX} -c ${SRC}/LayoutWriter.cpp -o LayoutWriter.o



clean:		
					rm -Rf *.o
					rm -Rf ${BIN}/LayoutTools
