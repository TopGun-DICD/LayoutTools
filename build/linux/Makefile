SRC=../../sources
BIN=../../bin
#CXX=g++ -Wall -std=c++0x
CXX=g++ -Wall -std=c++11

LIBS_GDS=GDSIIReaderASCII.o GDSIIReaderBIN.o GDSIIWriterASCII.o GDSIIWriterBIN.o GDSIIHelper.o
LIBS_MSK=MSKReader.o MSKWriter.o
LIBS_CIF=CIFReader.o CIFWriter.o
LIBS_DXF=DXFReader.o DXFWriter.o
LIBS_MAG=MAGReader.o MAGWriter.o
LIBS_OAS=OASReader.o OASWriter.o
all:		main

main:				$(LIBS_GDS) $(LIBS_MSK) $(LIBS_CIF) $(LIBS_DXF) $(LIBS_MAG) $(LIBS_OAS) \
					LayoutProcessing.o LayoutReader.o LayoutWriter.o ${SRC}/main.cpp
					@echo Building all together
					${CXX} -o ${BIN}/LayoutTools \
					$(LIBS_GDS) LayoutProcessing.o LayoutReader.o LayoutWriter.o \
					${SRC}/main.cpp 

#All for MSK
MSKReader.o:		${SRC}/LayoutReader_MSK.hpp ${SRC}/LayoutReader_MSK.cpp
					@echo Building MSK reader
					${CXX} -c ${SRC}/LayoutReader_MSK.cpp -o MSKReader.o

MSKWriter.o:		${SRC}/LayoutWriter_MSK.hpp ${SRC}/LayoutWriter_MSK.cpp
					@echo Building MSK writer
					${CXX} -c ${SRC}/LayoutWriter_MSK.cpp -o MSKWriter.o

#All for CIF
CIFReader.o:		${SRC}/LayoutReader_CIF.hpp ${SRC}/LayoutReader_CIF.cpp
					@echo Building CIF reader
					${CXX} -c ${SRC}/LayoutReader_CIF.cpp -o CIFReader.o

CIFWriter.o:		${SRC}/LayoutWriter_CIF.hpp ${SRC}/LayoutWriter_CIF.cpp
					@echo Building CIF writer
					${CXX} -c ${SRC}/LayoutWriter_CIF.cpp -o CIFWriter.o

#All for DXF
DXFReader.o:		${SRC}/LayoutReader_DXF.hpp ${SRC}/LayoutReader_DXF.cpp
					@echo Building DXF reader
					${CXX} -c ${SRC}/LayoutReader_DXF.cpp -o DXFReader.o

DXFWriter.o:		${SRC}/LayoutWriter_DXF.hpp ${SRC}/LayoutWriter_DXF.cpp
					@echo Building DXF writer
					${CXX} -c ${SRC}/LayoutWriter_DXF.cpp -o DXFWriter.o

#All for MAG
MAGReader.o:		${SRC}/LayoutReader_MAG.hpp ${SRC}/LayoutReader_MAG.cpp
					@echo Building MAG reader
					${CXX} -c ${SRC}/LayoutReader_MAG.cpp -o MAGReader.o

MAGWriter.o:		${SRC}/LayoutWriter_MAG.hpp ${SRC}/LayoutWriter_MAG.cpp
					@echo Building MAG writer
					${CXX} -c ${SRC}/LayoutWriter_MAG.cpp -o MAGWriter.o

#All for OAS
OASReader.o:		${SRC}/LayoutReader_OASIS.hpp ${SRC}/LayoutReader_OASIS.cpp
					@echo Building OASIS reader
					${CXX} -c ${SRC}/LayoutReader_OASIS.cpp -o OASReader.o

OASWriter.o:		${SRC}/LayoutWriter_OASIS.hpp ${SRC}/LayoutWriter_OASIS.cpp
					@echo Building OASIS writer
					${CXX} -c ${SRC}/LayoutWriter_OASIS.cpp -o OASWriter.o

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
