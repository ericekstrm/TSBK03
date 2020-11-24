#include "Model_Instance_Shader.h"


Model_Instance_Shader::Model_Instance_Shader()
    : Model_Shader("model_instance.vert", "model.frag")
{
}

void Model_Instance_Shader::load_instance_transforms(std::vector<mat4> const& transforms) const
{
    for (std::size_t i = 0; i < std::min(instance_max_count, transforms.size()); i++)
    {
        load_mat4("instance_transforms" + std::to_string(i) + "]", transforms[i]);
    }
}