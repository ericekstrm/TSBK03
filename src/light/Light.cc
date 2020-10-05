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