/*
 * LayoutWriter_GDSIIascii.hpp
 *
 * Calma binary GDSII file format writer by Artem K. Efremov
 * 03.07.2023
 */
#include "LayoutWriter_GDSIIascii.hpp"
#include "GDSIIHelperFunctions.hpp"
#include "GDSIITypes.hpp"

#include <ctime>

LayoutWriter_GDSIIascii::LayoutWriter_GDSIIascii() {

}

bool LayoutWriter_GDSIIascii::Write(const STR_CLASS &fileName, Layout *layout) {
    if (!layout)
        return false;

    if (fileName.empty())
        return false;

    file.open(fileName, std::ios::out | std::ios::binary);
    if (!file.is_open())
        return false;

    p_data = layout;

    WriteSection_HEADER();
    WriteSection_BEGINLIBRARY();

    for (size_t i = 0; i < layout->libraries.size(); ++i) {
        WriteSection_LIBNAME(layout->libraries[i]);
        WriteSection_UNITS(layout->libraries[i]);
        for (size_t j = 0; j < layout->libraries[i]->elements.size(); ++j) {
            WriteSection_BEGINSTRUCTURE(layout->libraries[i]->elements[j]);
            WriteSection_STRNAME(layout->libraries[i]->elements[j]);

            for (size_t k = 0; k < layout->libraries[i]->elements[j]->geometries.size(); ++k) {
                switch (layout->libraries[i]->elements[j]->geometries[k]->type) {
                case GeometryType::rectangle:
                    WriteSection_BOX(reinterpret_cast<Rectangle*>(layout->libraries[i]->elements[j]->geometries[k]));
                    break;
                case GeometryType::polygon:
                    WriteSection_BOUNDARY(reinterpret_cast<Polygon*>(layout->libraries[i]->elements[j]->geometries[k]));
                    break;
                case GeometryType::reference:
                    WriteSection_SREF(reinterpret_cast<Reference*>(layout->libraries[i]->elements[j]->geometries[k]));
                    break;
                case GeometryType::path:
                    WriteSection_PATH(reinterpret_cast<Path*>(layout->libraries[i]->elements[j]->geometries[k]));
                    break;
                }
            }

            WriteSection_ENDSTRUCTURE(layout->libraries[i]->elements[j]);
        }

        WriteSection_ENDLIBRARY(layout->libraries[i]);
    }

    file.close();

    return true;
}

void LayoutWriter_GDSIIascii::WriteSection_HEADER() {
    file << "HEADER ";
    int16_t versionNumber = 600;
    file << versionNumber << '\n';
}

void LayoutWriter_GDSIIascii::WriteSection_BEGINLIBRARY() {
    file << "BGNLIB ";

    std::time_t t = std::time(nullptr);
    std::tm now;

    localtime_s(&now, &t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m/%d/%Y %X", &now);
    std::string lastTimeAccessed = buffer;
    std::string lastTimeModified = lastTimeAccessed;
    
    file << lastTimeAccessed << ' ' << lastTimeModified << '\n';
}

void LayoutWriter_GDSIIascii::WriteSection_LIBNAME(Library* lib) {
    file << "LIBNAME " << lib->name << '\n';
}

void LayoutWriter_GDSIIascii::WriteSection_UNITS(Library* lib) {
    file << "UNITS " << lib->units.user << ' ' << lib->units.physical << '\n';
}

void LayoutWriter_GDSIIascii::WriteSection_ENDLIBRARY(Library* lib) {
    file << "ENDLIB ";
}

void LayoutWriter_GDSIIascii::WriteSection_BEGINSTRUCTURE(Element* element) {
    file << "\nBGNSTR ";

    std::time_t t = std::time(nullptr);
    std::tm now;

    localtime_s(&now, &t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m/%d/%Y %X", &now);
    std::string lastTimeAccessed = buffer;
    std::string lastTimeModified = lastTimeAccessed;

    file << lastTimeAccessed << ' ' << lastTimeModified << '\n';
}

void LayoutWriter_GDSIIascii::WriteSection_STRNAME(Element* element) {
    file << "STRNAME " << element->name << '\n';
}

void LayoutWriter_GDSIIascii::WriteSection_ENDSTRUCTURE(Element* element) {
    file << "ENDSTR \n";
}

void LayoutWriter_GDSIIascii::WriteSection_BOUNDARY(Polygon* polygon) {
    file << "\nBOUNDARY \n"
        << "LAYER " << polygon->layer << '\n'
        << "DATATYPE " << polygon->dataType << '\n';
    file << "XY ";
    for (const auto& coord : polygon->coords) {
        file << coord.x << ": " << coord.y << '\n';
    }
    file << "ENDEL \n";
}

void LayoutWriter_GDSIIascii::WriteSection_BOX(Rectangle* rectangle) {
    file << "\nBOX \n"
        << "LAYER " << rectangle->layer << '\n'
        << "DATATYPE " << rectangle->rectType << '\n';
    file << "XY ";
    for (const auto& coord : rectangle->coords) {
        file << coord.x << ": " << coord.y << '\n';
    }
    file << "ENDEL \n";
}

void LayoutWriter_GDSIIascii::WriteSection_SREF(Reference* reference) {
    file << "\nSREF \n"
        << "SNAME " << reference->name << '\n'
        << "XY " << reference->coords[0].x << ": " << reference->coords[0].y << '\n'
        << "ENDEL \n";
}

void LayoutWriter_GDSIIascii::WriteSection_PATH(Path* path) {
    file << "\nPATH \n"
        << "LAYER " << path->layer << '\n'
        << "DATATYPE " << path->dataType << '\n'
        << "PATHTYPE " << path->pathType << '\n'
        << "WIDTH " << path->width << '\n';
    file << "XY ";
    for (const auto& coord : path->coords) {
        file << coord.x << ": " << coord.y << '\n';
    }
    file << "ENDEL \n";
}
