#include "Game_State.h"
#include "Flying_Camera.h"
#include "Third_Person_Camera.h"
#include "settings.h"

#include <iostream>

Game_State::Game_State()
{
    /*for (float i = 1; i < 100; i++)
    {
        models.push_back(Model {"rock1", vec3{(float) (rand() % 128) - 64, 0, (float) (rand() % 128) - 64}});
    }
    models.push_back(Model {"door", vec3{10, 0, 0}});
    models.push_back(Model {"chair", vec3{0, 0, 5}});*/
    Model m {"rock1"};
    models.push_back(m);

    camera = std::make_unique<Flying_Camera>(vec3{20, 30, 20});

    lights.add_dir_light(vec3{-1, -1, 0}, vec3{0.988 / 2, 0.831 / 2, 0.251 / 2});
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

    //render to shadowmap
    shadowmap.activate();
    shadowmap.render(terrain);
    for (auto it = models.begin(); it != models.end(); it++)
    {
        shadowmap.render(*it);
    }
    shadowmap.render(terrain);
    shadowmap.render(tree1, tree_shader);
    shadowmap.deactivate();

    skybox_shader.start();
    skybox_shader.load_projection_matrix();
    skybox_shader.load_camera_matrix(camera->get_camera_matrix().remove_translation());
    skybox.render();
    skybox_shader.stop();

    //render normal
    shader.start();
    shader.load_projection_matrix();
    shader.load_camera_matrix(camera->get_camera_matrix());
    shader.load_camera_position(camera->get_position());
    shader.load_lights(lights);

    shader.load_light_space_matrix(shadowmap.get_position());
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, shadowmap.get_texture_id());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    for (auto it = models.begin(); it != models.end(); it++)
    {
        it->render(&shader);
    }

    terrain.render(&shader);

    shader.stop();

    tree_shader.start();
    tree_shader.load_projection_matrix();
    tree_shader.load_camera_matrix(camera->get_camera_matrix());

    tree1.render(tree_shader);

    tree_shader.stop();

    tree1.render_leafs(camera.get(), &lights);

    lights.render(projection, camera->get_camera_matrix());

    //shadow_map_image.render();
}

void Game_State::check_input(GLFWwindow * window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        change_state = "menu";
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        tree1.update(0);
    }

    camera->check_input(window);
}
void Game_State::activate(GLFWwindow* window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, static_cast<double>(window_width / 2.0), static_cast<double>(window_height / 2.0));

    // Exempel av hur man skulle kunna hantera enskilda knapptryckningar
    /*glfwSetKeyCallback(window, key_callback);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode){
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            auto self = static_cast<Game_State*>(glfwGetWindowUserPointer(window));
            self->set_state_flag("menu");
        }
    });*/
}

void Game_State::deactivate(GLFWwindow* window)
{

}