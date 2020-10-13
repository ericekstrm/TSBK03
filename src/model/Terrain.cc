#include "Terrain.h"
#include "stb_image.h"

#include <iostream>
#include <random>

Terrain::Terrain()
{
    generate_terrain();
    model_data.load_buffer_data(vertices, normals, texture_coords, indices);
    model_data.material.texture_id = load_texture("res/textures/container.jpg");
}

Terrain::~Terrain()
{
}

void Terrain::generate_terrain()
{
    //heightmap_terrain("island3.png");
    flat_terrain();
    
    set_indices();
}

void Terrain::flat_terrain()
{
    for (int i = -terrain_resolution / 2; i < terrain_resolution / 2 + 1; i++)
    {
        for (int j = -terrain_resolution / 2; j < terrain_resolution / 2 + 1; j++)
        {
            float r = 0;
            vertices.push_back(terrain_size / terrain_resolution * i);
            vertices.push_back(r);
            vertices.push_back(terrain_size / terrain_resolution * j);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            texture_coords.push_back(static_cast<float>(i) / terrain_resolution);
            texture_coords.push_back(static_cast<float>(j) / terrain_resolution);
        }
    }
}

void Terrain::heightmap_terrain(std::string const& file_name)
{
    std::vector<float> heightmap_data {};

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(("res/heightmaps/" + file_name).c_str(), &width, &height, &nrChannels, STBI_rgb);

    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "nr of channels: " << nrChannels << std::endl;
    if (data)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {

                unsigned bytePerPixel = 3;
                unsigned char* pixelOffset = data + (i + (width) * j) * bytePerPixel;
                unsigned char r = pixelOffset[0];
                //unsigned char g = pixelOffset[1];
                //unsigned char b = pixelOffset[2];
                //unsigned char a = nrChannels >= 4 ? pixelOffset[3] : 0xff;

                heightmap_data.push_back((float) r);
            }
        }
    } else
    {
        std::cout << "Failed to load heightmap: " << file_name << std::endl;
    }
    stbi_image_free(data);

    int k {0};
    for (int i = -terrain_resolution / 2; i < terrain_resolution / 2; i++)
    {
        for (int j = -terrain_resolution / 2; j < terrain_resolution / 2; j++)
        {
            float r = heightmap_data[k] / 256;
            vertices.push_back(terrain_size / terrain_resolution * i);
            vertices.push_back(r * max_height);
            vertices.push_back(terrain_size / terrain_resolution * j);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            texture_coords.push_back(static_cast<float>(i) / terrain_resolution);
            texture_coords.push_back(static_cast<float>(j) / terrain_resolution);

            k++;
        }
    }
}

void Terrain::set_indices()
{
    for (int i = 0; i < terrain_resolution - 1; i++)
    {
        for (int j = 0; j < terrain_resolution - 1; j++)
        {
            int topLeft = i * (terrain_resolution) +j;
            int topRight = topLeft + 1;
            int bottomLeft = (i + 1) * (terrain_resolution) +j;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
        }
    }
}
