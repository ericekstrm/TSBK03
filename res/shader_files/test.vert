#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_tex_coord;

uniform mat4 projection_matrix;
uniform mat4 world_matrix;
uniform mat4 model_matrix;

out vec2 texture_coord;

void main()
{
	gl_Position = projection_matrix * world_matrix * model_matrix * vec4(in_position, 1.0);
	texture_coord = in_tex_coord;
}
