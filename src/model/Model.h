#pragma once

#include "glad/glad.h"
#include "Vector.h"
#include "Matrix.h"
#include "OBJ_Loader.h"
#include "Shader.h"

#include <vector>
#include <string>

class Model
{
public:
    Model();
    Model(std::string const& file_name, vec3 const& position);
    ~Model();

    void update(float delta_time);
    virtual void render(Model_Shader const& shader) const;

    Matrix4 const get_model_matrix() const;

protected:
    void load_buffer_data(std::vector<float> const&, std::vector<float> const&, std::vector<int> const&);
    void load_texture(std::string file_name);

    unsigned int vao;
    unsigned int vb, tb, ib;
    unsigned int textureID;
    unsigned int indices_count {};

private:

    Model(std::vector<float> vertices, 
          std::vector<float> texture_coords, 
          std::vector<int> indices,
          objl::Material material);

    vec3 position {};
    vec3 scale {1, 1, 1};
    vec3 rotation {};
};
