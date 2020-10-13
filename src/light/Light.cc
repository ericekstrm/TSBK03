#include "Light.h"

void Light_Container::add_pos_light(vec3 const& position,  vec3 const& color)
{
    pos_lights.push_back(Pos_Light {position, color});
}

void Light_Container::add_dir_light(vec3 const& direction, vec3 const& color)
{
    dir_lights.push_back(Dir_Light {direction, color});
}

void Light_Container::render() const
{
    
}


std::vector<vec3> Light_Container::get_pos_dir_data() const
{
    std::vector<vec3> pos_dir_data {};
    for (auto it = pos_lights.begin(); it != pos_lights.end(); it++)
    {
        pos_dir_data.push_back(it->get_position());
    }
    for (auto it = dir_lights.begin(); it != dir_lights.end(); it++)
    {
        pos_dir_data.push_back(it->get_direction());
    }
    return pos_dir_data;
}

std::vector<vec3> Light_Container::get_color_data() const 
{
    std::vector<vec3> color_data {};
    for (auto it = pos_lights.begin(); it != pos_lights.end(); it++)
    {
        color_data.push_back(it->get_color());
    }
    for (auto it = dir_lights.begin(); it != dir_lights.end(); it++)
    {
        color_data.push_back(it->get_color());
    }
    return color_data;
}

std::vector<vec3> Light_Container::get_attenuation_data() const
{
    std::vector<vec3> attenuation_data {};
    for (auto it = pos_lights.begin(); it != pos_lights.end(); it++)
    {
        attenuation_data.push_back(it->get_attenuation());
    }
    for (auto it = dir_lights.begin(); it != dir_lights.end(); it++)
    {
        attenuation_data.push_back(vec3{0, 0, 0});
    }
    return attenuation_data; 
}

std::vector<int> Light_Container::get_light_type_data() const
{
    std::vector<int> light_type_data {};
    for (auto it = pos_lights.begin(); it != pos_lights.end(); it++)
    {
        light_type_data.push_back(0);
    }
    for (auto it = dir_lights.begin(); it != dir_lights.end(); it++)
    {
        light_type_data.push_back(1);
    }
    return light_type_data; 
}