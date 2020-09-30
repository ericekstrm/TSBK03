#version 400 core

in vec3 aPos;
in vec2 aTex;

uniform mat4 projection;
uniform mat4 camera_matrix;
uniform mat4 world_matrix;

out vec2 texture_coord;

void main()
{
	gl_Position = projection * camera_matrix * world_matrix * vec4(aPos, 1.0);
	texture_coord = aTex;
}
