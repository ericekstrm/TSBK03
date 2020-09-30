#include "RunState.h"
#include "Flying_Camera.h"
#include "Third_Person_Camera.h"

#include <iostream>

RunState::RunState()
{
    for (float i = 1; i < 10; i++)
    {
        models.push_back(Model {"crate", vec3 {0, 0, i * 10}});
    }
    models.push_back(Model {"door", vec3 {0, 0, 0}});
    models.push_back(Model {"chair", vec3 {0, 0, 5}});


    camera = std::make_unique<Flying_Camera>();
}

RunState::~RunState()
{
}

void RunState::update(float delta_time)
{
    for (auto it = models.begin(); it != models.end(); it++)
    {
        it->update(delta_time);
    }
    camera->update(delta_time);
}

void RunState::render() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox_shader.start();
    skybox_shader.load_projection_matrix(projection);
    skybox_shader.load_camera_matrix(camera->get_camera_matrix().remove_translation());
    skybox.render();
    skybox_shader.stop();

    shader.start();
    shader.load_projection_matrix(projection);
    shader.load_camera_matrix(camera->get_camera_matrix());

    for (auto it = models.begin(); it != models.end(); it++)
    {
        shader.load_world_matrix(it->get_model_matrix());
        it->render();
    }

    shader.load_world_matrix(terrain.get_model_matrix());
    terrain.render();

    shader.stop();
}

void RunState::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    camera->check_input(window);
}
