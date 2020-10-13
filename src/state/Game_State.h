#pragma once

#include "glad/glad.h"
#include "State.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Terrain.h"
#include "Skybox.h"
#include "Light.h"
#include "Tree.h"

#include <memory>

class Game_State : public State
{
public:
    Game_State();
    ~Game_State();

    virtual void update(float delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const { return "game"; };

private:
    Model_Shader shader {};
    std::vector<Model> models {};
    Terrain terrain {};

    std::unique_ptr<Camera> camera;

    Skybox_Shader skybox_shader {};
    Skybox skybox {};

    Light_Container lights {};

    Tree_Shader tree_shader {};
    Tree tree {};

    Matrix4 projection {fov_projection_matrix(45.0f, 1.0f, 0.1f, 100.0f)};
};
