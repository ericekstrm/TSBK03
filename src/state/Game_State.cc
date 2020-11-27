#include "Game_State.h"
#include "Flying_Camera.h"
#include "Third_Person_Camera.h"
#include "settings.h"

#include <iostream>

Game_State::Game_State()
{
    Model m {"rock1"};
    models.push_back(m);
    models.push_back(Model{"fence"});

    camera = std::make_unique<Flying_Camera>(vec3{20, 30, 20});

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

    lights.update(delta_time);
    shadowmap.set_light_position(lights.get_sun_position());
}

void Game_State::render() const
{
    //render to shadowmap
    shadowmap.activate();
    glCullFace(GL_FRONT);
    shadowmap.render(terrain);
    for (auto it = models.begin(); it != models.end(); it++)
    {
        shadowmap.render(*it);
    }
    shadowmap.render(terrain);
    shadowmap.render(tree1);
    glCullFace(GL_BACK);
    shadowmap.deactivate();

    main_fbo.bind();
    render_scene();
    main_fbo.unbind();

    sun_framebuffer.bind();
    render_godray_scene();
    sun_framebuffer.unbind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    main_image.render(lights.get_sun_screen_position(camera.get()));
}

void Game_State::render_scene() const
{
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, shadowmap.get_texture_id());

    for (auto it = models.begin(); it != models.end(); it++)
    {
        it->render(&shader);
    }

    terrain.render(&shader);

    tree1.render(&shader);
    tree2.render(&shader);
    tree3.render(&shader);

    shader.stop();

    tree1.render_leafs(camera.get(), &lights);
    tree2.render_leafs(camera.get(), &lights);
    tree3.render_leafs(camera.get(), &lights);

    lights.render(camera->get_camera_matrix());
}

void Game_State::render_godray_scene() const
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lights.render_sun(camera.get());

    god_ray_shader.start();
    god_ray_shader.load_projection_matrix();
    god_ray_shader.load_camera_matrix(camera->get_camera_matrix());

    for (auto it = models.begin(); it != models.end(); it++)
    {
        it->render(&god_ray_shader);
    }

    terrain.render(&god_ray_shader);

    tree1.render(&shader);
    tree2.render(&shader);
    tree3.render(&shader);

    god_ray_shader.stop();

    god_ray_leaf_shader.start();
    god_ray_leaf_shader.load_projection_matrix();
    god_ray_leaf_shader.load_camera_matrix(camera->get_camera_matrix());
    tree1.render_leafs(&god_ray_leaf_shader);
    tree2.render_leafs(&god_ray_leaf_shader);
    tree3.render_leafs(&god_ray_leaf_shader);
    god_ray_leaf_shader.stop();
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
        tree2.update(0);
        tree3.update(0);
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

void Game_State::deactivate(GLFWwindow*)
{

}