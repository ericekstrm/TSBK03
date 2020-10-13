#pragma once

#include "Model.h"

class Terrain : public Model
{
public:
    Terrain();
    ~Terrain();

private:

    // Terrain_size is the size that the texture "tile" will take up in the world.
    float terrain_size = 128;
    // Terrain_resolution is the number of vertices in each dimension of the texture "tile".
    // Also then the size in each dimension of the heightmap image file.
    int terrain_resolution = 512;

    float max_height {2};

    void generate_terrain();
    void flat_terrain();
    void heightmap_terrain(std::string const& file_name);

    void set_indices();

    std::vector<float> vertices = {};
    std::vector<float> normals {};
    std::vector<float> texture_coords = {};
    std::vector<int> indices = {};
};
