#pragma once

#include "GL/gl.h"

#include "Tree.h"
#include "Shader.h"
#include "Model_Shader.h"
#include "Terrain.h"

class Shadowmap
{
public:
    Shadowmap(vec3 const& light_position);

    void activate() const;
    void deactivate() const;

    void render(Tree const& tree, Tree_Shader const& shader) const;
    void render(Terrain const& terrain) const;
    void render(Model const& model) const;

    unsigned get_texture_id() const { return depth_map; }
    vec3 get_position() const { return light_position; }

private:

    static const int shadow_width = 2014;
    static const int shadow_height = 2014;

    unsigned depth_map_fbo {0};
    unsigned depth_map {0};

    vec3 light_position {};

    Model_Shader shader {"shadow.vert", "shadow.frag"};
};