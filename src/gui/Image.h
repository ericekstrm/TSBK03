#pragma once

#include "Vector.h"
#include "Shader.h"

class Image
{
public:
    Image(vec2 const& position, vec2 size, std::string image_file);
    Image(vec2 const& position, vec2 size, unsigned texture_id);

    void render() const;

private:
    vec2 position;
    vec2 size;

    void create_mesh();

    //opengl 
    unsigned vao;
    unsigned vb;
    unsigned tb;
    unsigned ib;
    int indices_count;
    int texture_id;

    Image2D_Shader shader {};
};
