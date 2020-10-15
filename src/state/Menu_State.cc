#include "Menu_State.h"

#include <iostream>

#include "glad/glad.h"

Menu_State::Menu_State()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Menu_State::~Menu_State()
{
}

void Menu_State::update(float delta_time)
{
}

void Menu_State::render() const
{
    glClear(GL_COLOR_BUFFER_BIT);

    text.render();
}

void Menu_State::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
