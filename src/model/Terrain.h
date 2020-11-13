#pragma once

#include "Model.h"

class Heightmap
{
public:
    Heightmap(std::string const& file_name);
    float get_height(int x, int z) const;
    vec3 get_normal(int x, int z) const;
    
private:
    int width;
    int height;
    std::vector<float> heightmap_data {};
};

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

    float max_height {20};

    void generate_terrain();
    void set_indices();

    //terrain generation functions
    void flat_terrain();
    void heightmap_terrain(std::string const& file_name);
    void generate_perlin_terrain();

    //perlin noise functions
    float get_perlin_height(int x, int z) const;
    float generate_perlin_noise(int x, int z) const;
    float generate_interpolated_height(float x, float z) const;
    float interpolate(float p1, float p2, float blend) const;

    std::vector<float> vertices = {};
    std::vector<float> normals {};
    std::vector<float> texture_coords = {};
    std::vector<int> indices = {};
};
