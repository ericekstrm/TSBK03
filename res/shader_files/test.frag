#version 400 core

in vec2 texture_coord;

uniform sampler2D kd_texture;

out vec4 outColor;

void main()
{
	outColor = texture(kd_texture, texture_coord);
}
