#version 400 core

in vec3 out_normal;
in vec2 out_tex_coord;
in vec3 out_fragment_position;

out vec4 out_color;

// Material
uniform sampler2D kd_texture;
uniform sampler2D specularity_map;
uniform bool use_specularity_map;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float a;

uniform vec3 camera_pos;

// Light
uniform int number_of_lights;
uniform vec3 light_pos_dir[10];
uniform vec3 light_color[10];
uniform vec3 light_attenuation_params[10];
uniform bool light_type[10];

void main(void)
{
	vec3 temp_color = vec3(0, 0, 0);

	for (int i = 0; i < number_of_lights; i++)
	{
		vec3 light_dir;
		float attenuation = 1;
		
		if(light_type[i])
		{
			light_dir = -normalize(light_pos_dir[i]);
			attenuation = 1.0;
		} else
		{
			light_dir = normalize(light_pos_dir[i] - out_fragment_position);
			float constant = light_attenuation_params[i].x;
 			float linear = light_attenuation_params[i].y;	
 			float quadratic = light_attenuation_params[i].z;

			float distance = distance(light_pos_dir[i], out_fragment_position);
			attenuation = 1.0 / (constant + linear * distance + quadratic * pow(distance, 2));
		}
				
		vec3 normal = normalize(out_normal);
		
		// Diffuse
		float diffuse = max(dot(normal, light_dir), 0.0);
		vec3 diffuse_light = kd * diffuse * light_color[i];

		// Specular
		/*vec3 view_dir = normalize(camera_pos - out_fragment_position);
		vec3 reflection = reflect(-light_dir, normal);
		float specular = max(dot(reflection, view_dir), 0.0);

		vec3 specular_light = vec3(0,0,0);
		if(use_specularity_map)
		{
			vec3 spec_map = texture(specularity_map, out_tex_coord).rgb;
			specular_light = ks * pow(specular, a) * spec_map * light_color[i];
		}
		else
		{
			specular_light = ks * pow(specular, a) * light_color[i];
		}*/

		temp_color += (diffuse_light) * attenuation;
	}

	temp_color +=  ka / 5;

	vec4 tex = texture(kd_texture, out_tex_coord);
	out_color = vec4(temp_color, 1.0) * tex;
}
