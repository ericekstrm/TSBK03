#pragma once

#ifdef WIN32
    #include "glad/glad.h"
#else
    #include "GL/gl.h"
#endif

#include "State.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Terrain.h"
#include "Skybox.h"
#include "Light.h"
#include "Tree.h"
#include "Shadowmap.h"
#include "Image.h"

#include <memory>

class Game_State : public State
{
public:
    Game_State();
    ~Game_State();

    virtual void update(float delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const { return "game"; }

    void activate(GLFWwindow* window) override;
    void deactivate(GLFWwindow* window) override;

private:
    Model_Shader shader {};
    Model_Shader shader2 {"shadow.vert", "shadow.frag"};
    std::vector<Model> models {};
    Terrain terrain {};

    std::unique_ptr<Camera> camera;

    Skybox_Shader skybox_shader {};
    Skybox skybox {};

    Light_Container lights {};

    Tree_Shader tree_shader {};
    Tree tree1 {vec3{0,0,0}};

    Shadowmap shadowmap {vec3{5, 5, 5}};

    Image shadow_map_image {vec2{0.5,0.5}, vec2{0.5,0.5}, shadowmap.get_texture_id()};
};
