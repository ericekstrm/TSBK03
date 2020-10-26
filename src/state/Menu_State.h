#pragma once

#include "State.h"
#include "Text.h"
#include "Button.h"
#include "Image.h"

class Menu_State : public State
{
public:
    Menu_State();
    ~Menu_State();

    virtual void update(float delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const { return "menu"; }

    void activate(GLFWwindow* window) override;
    void deactivate(GLFWwindow* window) override;

private:
    Font font {"arial", 48};
    Text text {"Tree Simulator", vec2{-0.9, 0.9}, font};

    Image image1 {vec2{0, 0}, vec2{1, 1}, "res/images/1.png"};

    //Button button {vec2{0, 0}, vec2{0.2, 0.2}, "test!", []() { std::cout << "heeeeeeeeej!!" << std::endl; }};

    unsigned vao;
    unsigned vb;
    unsigned ib;
    int indices_count;

    Shader shader {"pass.vert", "pass.frag"};
};
