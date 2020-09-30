#include "Model.h"

#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <string>
#include <iostream>

Model::Model()
    : Model {Vector<3>{0, 0, 0}}
{
}

Model::Model(Vector<3> const & position)
    : position {position}
{
    //TODO: load vertices and indices

    load_texture("container.jpg");
    load_buffer_data(vertices, texture_coords, indices);
}

Model::Model(std::vector<float> vertices, std::vector<float> texture_coords, std::vector<int> indices, objl::Material material)
{
    load_buffer_data(vertices, texture_coords, indices);
}

Model::~Model()
{
}

void Model::update(float delta_time)
{
}

void Model::render() const
{
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
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

void Model::load_buffer_data(std::vector<float> const& vertices, 
                             std::vector<float> const& texture_coords,
                             std::vector<int> const& indices)
{
    load_VAO();

    load_vertices_VBO(vertices);
    load_textures_VBO(texture_coords);
    load_indices_VBO(indices);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::load_texture(std::string file_name)
{
    // load and create a texture 

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //ändra dessa för att ta bort flimmer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, STBI_rgb);
    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
            glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        std::cout << "Failed to load texture:" << file_name <<  std::endl;
    }
    stbi_image_free(data);
}

void Model::load_VAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void Model::load_vertices_VBO(std::vector<float> const& vertices)
{
    int vertices_attrib_array = 0;
    glGenBuffers(1, &VBOvertices);
    glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(vertices_attrib_array, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
}

void Model::load_textures_VBO(std::vector<float> const & texture_coords)
{
    int texture_attrib_array = 1;
    glGenBuffers(1, &VBOtextures);
    glBindBuffer(GL_ARRAY_BUFFER, VBOtextures);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texture_coords.size(), &texture_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(texture_attrib_array, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
}

void Model::load_indices_VBO(std::vector<int> const& indices)
{
    glGenBuffers(1, &VBOindices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices[0], GL_STATIC_DRAW);
    indices_count = indices.size();
}