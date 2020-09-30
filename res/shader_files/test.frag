#version 400 core

in vec2 texture_coord;

uniform sampler2D tex;

out vec4 outColor;

void main()
{
	outColor = texture(tex, texture_coord);
}
