#include "Menu_State.h"

#include <iostream>

#include "settings.h"
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

    image1.render();
}

void Menu_State::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        change_state = "game";
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        std::cout << "helo" << std::endl;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // normalize mouse position
        xpos = xpos / window_width * 2 - 1;
        ypos = ypos / window_height * 2 - 1;

        //button.try_click(vec2{xpos, ypos});
    }
}

void Menu_State::activate(GLFWwindow* window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Menu_State::deactivate(GLFWwindow* window)
{
}