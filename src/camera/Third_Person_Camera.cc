#include "Third_Person_Camera.h"

void Third_Person_Camera::check_input(GLFWwindow* window)
{
    velocity = vec3 {0, 0, 0};
    vec3 fly_dir {direction};
    fly_dir[1] = 0;
    vec3 bi_dir {cross(up_vector, fly_dir)};

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        velocity += fly_dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        velocity -= fly_dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        velocity += bi_dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        velocity -= bi_dir * speed;
    }


    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    direction = rotation_matrix((cursor_point_x - xpos) / 10, 0, 1, 0) * direction;
    vec3 d = cross(direction, up_vector);
    direction = rotation_matrix((cursor_point_y - ypos) / 10, d[0], d[1], d[2]) * direction;

    glfwSetCursorPos(window, cursor_point_x, cursor_point_y);
}
