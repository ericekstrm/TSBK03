#include "Model.h"

#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <string>
#include <iostream>

Model::Model()
    : Model {"door", vec3{0, 0, 0}}
{
}

Model::Model(std::string const& file_name, vec3 const & position)
    : position {position}
{
    load_model(file_name);
}

Model::Model(std::vector<float> vertices, std::vector<float> texture_coords, std::vector<int> indices, objl::Material material)
{
    model_data.load_buffer_data(vertices, texture_coords, indices);
}

Model::~Model()
{
}

void Model::update(float delta_time)
{
}

void Model::render(Model_Shader const& shader) const
{
    glBindVertexArray(model_data.vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model_data.material.texture_id);

    shader.load_model_matrix(get_model_matrix());

    glDrawElements(GL_TRIANGLES, model_data.indices_count, GL_UNSIGNED_INT, 0);
}

Matrix4 const Model::get_model_matrix() const
{
    Matrix4 t {translation_matrix(position[0], position[1], position[2])};
    Matrix4 s {scale_matrix(scale[0], scale[1], scale[2])};
    Matrix4 r {
        rotation_matrix(rotation[0], 1, 0, 0) * 
        rotation_matrix(rotation[1], 0, 1, 0) *
        rotation_matrix(rotation[2], 0, 0, 1)};

    return (t * r * s);
}

Model::Material Model::get_material() const
{
    return model_data.material;
}

unsigned int Model::load_texture(std::string file_name) const
{
    unsigned int tex_id {0};

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, STBI_rgb);
    if (data)
    {
        glGenTextures(1, &tex_id);
        glBindTexture(GL_TEXTURE_2D, tex_id);

        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //ändra dessa för att ta bort flimmer
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        //TODO: byt till att kasta ett undantag.
        std::cout << "Failed to load texture: " << file_name <<  std::endl;
    }
    stbi_image_free(data);

    return tex_id;
}

void Model::load_model(std::string const& file_name)
{
    Model_Data current_model;

    auto it = models.find(file_name);
    if ( it != models.end())
    {
        current_model = it->second;
    } else
    {
        current_model = load_model_from_file(file_name);
        models[file_name] = current_model;
    }

    model_data = current_model;
}

Model::Model_Data Model::load_model_from_file(std::string const& file_name) const
{
    objl::Loader obj_loader {};
    
    if (obj_loader.LoadFile("res/objects/" + file_name + "/" + file_name + ".obj"))
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

        objl::Material mat = obj_loader.LoadedMaterials[0];

        bool use_specularity_map {false};
        unsigned int specularity_map {};
        unsigned int kd_texture {load_texture("res/objects/" + file_name + "/" + mat.map_Kd)};
        if (mat.map_Ks != "")
        {
            specularity_map = load_texture("res/objects/" + file_name + "/" + mat.map_Ks);
            use_specularity_map = true;
        }
        Material material {kd_texture, specularity_map, use_specularity_map, mat.Ka, mat.Kd, mat.Ks, mat.Ni};

        Model_Data model_data {};
        model_data.material = material;
        model_data.load_buffer_data(vertices, texture_coords, indices);
        return model_data;

    } else
    {
        throw std::runtime_error("Cound not find model: " + file_name);
    }
}

void Model::Model_Data::load_buffer_data(std::vector<float> const& vertices, 
                             std::vector<float> const& texture_coords,
                             std::vector<int> const& indices)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    int vertices_attrib_array = 0;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(vertices_attrib_array, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    /*int normal_attrib_array = 1;
    glGenBuffers(1, &VBOnormals);
    glBindBuffer(GL_ARRAY_BUFFER, VBOnormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texture_coords.size(), &texture_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(texture_attrib_array, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);*/

    int texture_attrib_array = 1;
    glGenBuffers(1, &tb);
    glBindBuffer(GL_ARRAY_BUFFER, tb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texture_coords.size(), &texture_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(texture_attrib_array, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);

    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices[0], GL_STATIC_DRAW);
    indices_count = indices.size();
    
    glEnableVertexAttribArray(vertices_attrib_array);
    //glEnableVertexAttribArray(normal_attrib_array);
    glEnableVertexAttribArray(texture_attrib_array);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}