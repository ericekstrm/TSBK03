#include "Vector.h"

class Pos_Light;
class Dir_Light;

class Light_Container
{
public:
    void add_pos_light(vec3 const& position,  vec3 const& color);
    void add_dir_light(vec3 const& direction, vec3 const& color);

    void render() const;

private:
    std::vector<Pos_Light> pos_lights {};
    std::vector<Dir_Light> dir_lights {};
};

class Pos_Light
{
public:
    Pos_Light(vec3 const& pos, vec3 const& color)
        : pos {pos}, color {color} {}

    vec3 get_position() const { return pos; }
    vec3 get_color() const { return color; }

private:
    vec3 pos;
    vec3 color {1, 1, 1};
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