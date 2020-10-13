#version 400 core

layout (location = 0) in vec3 in_position;

uniform mat4 projection_matrix;
uniform mat4 world_matrix;
uniform mat4 model_matrix;

void main()
{
    gl_Position = projection_matrix * world_matrix * model_matrix * vec4(in_position, 1.0);
}
