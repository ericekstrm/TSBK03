#pragma once

#include "State.h"
#include "Text.h"

class Menu_State : public State
{
public:
    Menu_State();
    ~Menu_State();

    virtual void update(float delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const { return "menu"; };

private:
    Font font {"arial", 512};
    Text text {"detta vara text!", vec2{-1, -1}, font};

    unsigned vao;
    unsigned vb;
    unsigned ib;
    int indices_count;

    Shader shader {"pass.vert", "pass.frag"};
};
