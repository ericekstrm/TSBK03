#pragma once

#include "Vector.h"

class Pos_Light;
class Dir_Light;

class Light_Container
{
public:
    void add_pos_light(vec3 const& position,  vec3 const& color);
    void add_dir_light(vec3 const& direction, vec3 const& color);

    void render() const;

    int get_number_of_lights() const {return pos_lights.size() + dir_lights.size(); }
    
    std::vector<vec3> get_pos_dir_data() const;
    std::vector<vec3> get_color_data() const;
    std::vector<vec3> get_attenuation_data() const;
    std::vector<int> get_light_type_data() const;

private:
    std::vector<Pos_Light> pos_lights {};
    std::vector<Dir_Light> dir_lights {};
};

class Pos_Light
{
public:
    Pos_Light(vec3 const& pos, vec3 const& color)
        : pos {pos}, color {color}, attenuation{1.0, 0.045, 0.0075} {}

    vec3 get_position() const { return pos; }
    vec3 get_color() const { return color; }
    vec3 get_attenuation() const { return attenuation; }

private:
    vec3 pos;
    vec3 color {1, 1, 1};
    vec3 attenuation;
};

class Dir_Light
{
public:
    Dir_Light(vec3 const& dir, vec3 const& color)
        : dir {dir}, color {color} {}

    vec3 get_direction() const {return dir; }
    vec3 get_color() const { return color; }

private:
    vec3 dir;
    vec3 color {1, 1, 1};
};