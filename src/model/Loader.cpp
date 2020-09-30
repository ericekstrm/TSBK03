#include "Loader.h"
#include "OBJ_Loader.h"

#include <iostream>

std::string Loader::model_obj_folder = "res/objects/";

Model Loader::load_model(std::string const& file_name)
{

    objl::Loader obj_loader {};
    
    if (obj_loader.LoadFile(model_obj_folder + file_name + "/" + file_name + ".obj"))
    {
        std::vector<float> vertices {};
        std::vector<int> indices {};
        std::vector<float> texture_coords {};

        for (auto it = obj_loader.LoadedVertices.begin(); it != obj_loader.LoadedVertices.end(); it++)
        {
            vertices.push_back(it->Position.X);
            vertices.push_back(it->Position.Y);
            vertices.push_back(it->Position.Z);
            texture_coords.push_back(it->TextureCoordinate.X);
            texture_coords.push_back(it->TextureCoordinate.Y);
        }

        for (auto it = obj_loader.LoadedIndices.begin(); it != obj_loader.LoadedIndices.end(); it++)
        {
            indices.push_back(*it);
        }

        objl::Material material = obj_loader.LoadedMaterials[0];

        Model m {vertices, texture_coords, indices, material};
        m.load_texture(model_obj_folder + file_name + "/" + material.map_Kd);

        return m;
    } else
    {
        throw std::runtime_error("Cound not find file.");
    }
}
