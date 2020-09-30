#pragma once

#include <GLFW/glfw3.h>

#include "Vector.h"
#include "Matrix.h"

class Camera
{
public:
    Camera();
    ~Camera();

    virtual void update(float delta_time);
    virtual void check_input(GLFWwindow* window);

    Matrix4 get_camera_matrix() const;

protected:
    vec3 position {2, 2, 2};
    vec3 direction {-2, -2, -2};
    vec3 up_vector {0, 1, 0};

    vec3 velocity {};
    float speed = 20;

    double cursor_point_x {200};
    double cursor_point_y {200};
};
