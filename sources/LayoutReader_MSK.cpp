/*
 * LayoutReader_MSK.cpp
 *
 * uWind (MicroWind) MSK file format reader by Mikhail S. Kotlyarov
 * 02.10.2021
 */

#include "LayoutReader.hpp"
#define _CRT_SECURE_NO_WARNINGS

bool LayoutReader_MSK::IsMyFormat(const std::string& fName)
{
    size_t comma_pos = fName.find_last_of(".");
    if (comma_pos == std::string::npos)
        return false;
    fileName = fName;
    std::string file_extention = fName.substr(comma_pos + 1, fName.length() - comma_pos);

    if (file_extention == "MSK")
        return true;
    if (file_extention == "msk")
        return true;

    return false;
}
bool LayoutReader_MSK::Read(LayoutData* layout)
{
    if (!layout)
        return false;

    file.open(fileName);
    if (!file.is_open())
        return false;

    p_data = layout;
  
    p_active_library = new Library;
    p_active_element = new Element;

    p_data->fileName = this->fileName;
    p_active_element->name = this->fileName;
    p_active_library->name = this->fileName;
    //Переменная для хранения одной строки из файла
    std::string line_from_file;
    //Множество названий всех слоев
    std::unordered_set <std::string> all_layer_names;
    //Переменная для проверки корректности ввода
    bool is_Bounding_Box_filled = false;

    while (std::getline(file,line_from_file))
    {
        Coord left_bot;
        Coord right_top;
        std::string layer_name;

        if (!is_Bounding_Box_filled)
        {
            if (read_Bounding_box_coords(line_from_file, left_bot, right_top))
            {
               
                const std::string BB_name = "BB";
                GeometryItem* current_box = new GeometryItem_Box;
                fill_GeometryItem_box(current_box, left_bot, right_top);
                p_active_element->items.push_back(current_box);

                Layer BB_layer;
                BB_layer.layer = static_cast<int16_t>(all_layer_names.size() + 1);
                BB_layer.name = BB_name;
                BB_layer.items.push_back(current_box);
                all_layer_names.insert(BB_name);

                p_active_library->layers.push_back(BB_layer);
                is_Bounding_Box_filled = true;
            }

        }
        else if (read_Rectangle_coords(line_from_file, left_bot, right_top, layer_name))
        {
            GeometryItem* current_box = new GeometryItem_Box;
            fill_GeometryItem_box(current_box, left_bot, right_top);
            p_active_element->items.push_back(current_box);


            const int16_t founded_index = my_index_find(all_layer_names, layer_name);
            if (founded_index == -1)
            {
                Layer current_layer;
                current_layer.layer = static_cast<int16_t>(all_layer_names.size() + 1);
                current_layer.name = layer_name;
                current_layer.items.push_back(current_box);
                all_layer_names.insert(layer_name);
                p_active_library->layers.push_back(current_layer);
            }
            else
            {
                p_active_library->layers.at(founded_index).items.push_back(current_box);
            }
            
        }



        

    }
  
    p_active_library->elements.push_back(p_active_element);
    p_data->libraries.push_back(p_active_library);
   
    
    file.close();
    return true;
    
}



inline bool LayoutReader_MSK::read_Bounding_box_coords(const std::string& line, Coord& left_bot, Coord& right_top)
{
    if (!sscanf_s(line.c_str(), "BB(%d,%d,%d,%d)", &left_bot.x, &left_bot.y, &right_top.x, &right_top.y))
        return false;
    return true;
}

inline bool LayoutReader_MSK::read_Rectangle_coords(const std::string& line, Coord& left_bot, Coord& right_top, std::string& layer_name)
{
    char c_layer_name[4];
    int width = 0, height = 0;

    if (!sscanf_s(line.c_str(), "REC(%d,%d,%d,%d,%s)", &left_bot.x, &left_bot.y, &width, &height, c_layer_name,4))
    {
        return false;
    }

    c_layer_name[strlen(c_layer_name) - 1] = '\0';
    layer_name = c_layer_name;
    right_top.x = left_bot.x + width;
    right_top.y = left_bot.y + height;

    
   
    return true;
}

void LayoutReader_MSK::fill_GeometryItem_box(GeometryItem* filling_box, const Coord& left_bot, const Coord& right_top)
{
    Coord curr_coord;
    int32_t dx = calculate_delta(left_bot.x, right_top.x);
    int32_t dy = calculate_delta(left_bot.y, right_top.y);

    //Left top
    curr_coord.x = right_top.x - dx;
    curr_coord.y = right_top.y;
    filling_box->coords.push_back(curr_coord);
    
    //Right top
    filling_box->coords.push_back(right_top);

    //Right bot
    curr_coord.x = right_top.x;
    curr_coord.y = right_top.y - dy;
    filling_box->coords.push_back(curr_coord);

    //Left bot
    curr_coord.x = right_top.x - dx;
    curr_coord.y = right_top.y - dy;
    filling_box->coords.push_back(curr_coord);

    //Left top
    curr_coord.x = right_top.x - dx;
    curr_coord.y = right_top.y;
    filling_box->coords.push_back(curr_coord);

    

    
}

inline int32_t LayoutReader_MSK::calculate_delta(const int32_t first,const int32_t second) {
    return second - first;
}

int16_t LayoutReader_MSK::my_index_find(const std::unordered_set<std::string>& current_set, const std::string& str)
{
    uint16_t index_find_str = 0;

    for (auto i = current_set.begin(); i != current_set.end(); i++)
    {
        if (str == *i)
        {
            return index_find_str;
        }
        index_find_str++;
    }

    return -1;
}
