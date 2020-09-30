#version 330 core

in vec3 in_Position;
in vec3 texCoord;

out vec3 TexCoords;

uniform mat4 camera_matrix;
uniform mat4 projection;

void main()
{
    TexCoords = in_Position;
    gl_Position = projection * camera_matrix * vec4(in_Position, 1.0);
}
