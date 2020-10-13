#include "Game_State.h"
#include "Flying_Camera.h"
#include "Third_Person_Camera.h"

#include <iostream>

Game_State::Game_State()
{
    /*for (float i = 1; i < 100; i++)
    {
        models.push_back(Model {"rock1", vec3{(float) (rand() % 128) - 64, 0, (float) (rand() % 128) - 64}});
    }
    models.push_back(Model {"door", vec3{10, 0, 0}});
    models.push_back(Model {"chair", vec3{0, 0, 5}});*/

    camera = std::make_unique<Flying_Camera>(vec3{10, 5, 10});

    lights.add_dir_light(vec3{-1, -1, 0}, vec3{0.988, 0.831, 0.251});
    lights.add_pos_light(vec3{0, 5, 5}, vec3{1, 1, 1});
    lights.add_pos_light(vec3{50, 3, 0}, vec3{1, 0, 0});
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
    shader.load_camera_position(camera->get_position());
    shader.load_lights(lights);

    for (auto it = models.begin(); it != models.end(); it++)
    {
        it->render(shader);
    }

    terrain.render(shader);

    shader.stop();

    lights.render();

    tree_shader.start();
    tree_shader.load_projection_matrix(projection);
    tree_shader.load_camera_matrix(camera->get_camera_matrix());

    tree.render(tree_shader);

    tree_shader.stop();
}

void Game_State::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    camera->check_input(window);
}
