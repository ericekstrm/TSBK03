#version 330 core

in vec3 out_tex_coords;

uniform samplerCube cube_map;
uniform vec3 fogColor;

out vec4 outColor;

const float lowerFogLimit = 0;
const float upperFogLimit = 0.5;

void main()
{
    vec4 finalColor = texture(cube_map, out_tex_coords);
	outColor = finalColor;

    //float fogFactor = (TexCoords.y - lowerFogLimit) / (upperFogLimit - lowerFogLimit);
    //fogFactor = clamp(fogFactor, 0, 1);
    //outColor = mix(vec4(fogColor, 1), finalColor, fogFactor);
}
