#version 400 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coord;

out vec3 out_normal;
out vec2 out_tex_coord;
out vec3 out_fragment_position;

uniform mat4 model_matrix;
uniform mat4 world_matrix;
uniform mat4 projection_matrix;

void main(void)
{
	mat3 normal_matrix = mat3(model_matrix);
	out_normal = normal_matrix * in_normal;
	out_tex_coord = in_tex_coord;
	out_fragment_position = vec3(model_matrix * vec4(in_position, 1.0));
	gl_Position = projection_matrix * world_matrix * model_matrix * vec4(in_position, 1.0);
}
