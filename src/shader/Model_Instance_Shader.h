#pragma once

#include "Model_Shader.h"

#include <array>

const std::size_t instance_max_count {200};

class Model_Instance_Shader : public Model_Shader
{
public:
    Model_Instance_Shader();

    void load_instance_transforms(std::vector<mat4> const& transforms) const;
};