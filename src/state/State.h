#pragma once

#include <GLFW/glfw3.h>
#include <string>

class State
{
public:
    State()
    {

    };
    ~State()
    {

    };

    virtual void update(float delta_time) = 0;
    virtual void render() const = 0;
    virtual void check_input(GLFWwindow* window) = 0;
    virtual std::string name() const = 0;

    std::string update_state()
    {
        std::string tmp {change_state};
        change_state = "";
        return tmp;
    }

private:
    std::string change_state {};
};
