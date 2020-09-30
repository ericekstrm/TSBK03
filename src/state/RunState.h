#pragma once

#include "glad/glad.h"
#include "State.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Terrain.h"
#include "Skybox.h"

#include <memory>

class RunState : public State
{
public:
    RunState();
    ~RunState();

    virtual void update(float delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const
    {
        return "run";
    };
private:
    Shader shader {};
    std::vector<Model> models {};
    std::unique_ptr<Camera> camera;
    Terrain terrain {};

    Shader skybox_shader {"skybox.vert", "skybox.frag"};
    Skybox skybox {};

    Matrix4 projection {fov_projection_matrix(45.0f, 1.0f, 0.1f, 100.0f)};
};
