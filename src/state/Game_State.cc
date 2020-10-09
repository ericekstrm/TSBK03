#include "Game_State.h"
#include "Flying_Camera.h"
#include "Third_Person_Camera.h"

#include <iostream>

Game_State::Game_State()
{
    for (float i = 1; i < 100; i++)
    {
        models.push_back(Model {"pine", vec3 {(float) (rand() % 128) - 64, 0, (float) (rand() % 128) - 64}});
    }
    models.push_back(Model {"door", vec3 {0, 0, 0}});
    models.push_back(Model {"chair", vec3 {0, 0, 5}});

    camera = std::make_unique<Flying_Camera>();

    lights.add_pos_light(vec3{0, 1, 1}, vec3 {0, 1, 0});
    lights.add_pos_light(vec3{2, 1, 0}, vec3 {1, 0, 0});
}

Game_State::~Game_State()
{
}

void Game_State::update(float delta_time)
{
    for (auto it = models.begin(); it != models.end(); it++)
    {
        it->update(delta_time);
    }
    camera->update(delta_time);
}

void Game_State::render() const
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
        it->render(shader);
    }

    terrain.render(shader);

    shader.stop();

    lights.render();
}

void Game_State::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    camera->check_input(window);
}
