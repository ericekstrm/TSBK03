#version 400 core

in VS_OUT {
	vec3 normal;
	vec2 tex_coord;
	vec3 fragment_position;
	vec4 fragment_position_light_space;
} fs_in;

out vec4 out_color;

// Material
uniform sampler2D kd_texture;
uniform sampler2D specularity_map;
uniform bool use_specularity_map;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float specular_exponent;

uniform vec3 camera_pos;

/*uniform POS_LIGHT {
	vec3 position;
	vec3 color;
	vec3 attenuation_constant;
	vec3 attenuation_linear;
	vec3 attenuation_quadratic;
} pos_lights[10];*/

/*uniform DIR_LIGHT {
	vec3 direction;
	vec3 color;
} dir_lights[10];*/

// Light
uniform int number_of_lights;
uniform vec3 light_pos_dir[10];
uniform vec3 light_color[10];
uniform vec3 light_attenuation_params[10];
uniform bool light_type[10];

//forward declarations
vec3 calc_light(vec3, vec3, vec3, vec3);

void main(void)
{
	//calc normal
	vec3 normal = normalize(fs_in.normal);

	//calc view dir
	vec3 view_dir = normalize(camera_pos - fs_in.fragment_position);

	//calc material colors
	
	//vec3 mat_ambient = ka;
	//vec3 mat_diffuse = vec3(1, 1, 1);
	//vec3 mat_specular = ks;
	//... gör massa mer i java

	vec3 output = vec3(0, 0, 0);

	//add ambient light
	output += ka * 0.2;

	//add directional light
	for (int i = 0; i < number_of_lights; i++)
	{
		if (light_type[i])
		{
			vec3 light_dir = -normalize(light_pos_dir[i]);

			//float shadow = calc_shadow(fragment_position_light_space);
		
			output += calc_light(normal, light_dir, light_color[i], view_dir);
		} else
		{
			vec3 light_dir = normalize(light_pos_dir[i] - fs_in.fragment_position);

			float attenuation_constant = light_attenuation_params[i].x;
 			float attenuation_linear = light_attenuation_params[i].y;	
 			float attenuation_quadratic = light_attenuation_params[i].z;

			float distance = length(light_pos_dir[i] - fs_in.fragment_position);
			float attenuation = 1.0 / (attenuation_constant + attenuation_linear * distance + attenuation_quadratic * distance * distance);

			output += attenuation * calc_light(normal, light_dir, light_color[i], view_dir);
		}
	}

	out_color = vec4(output, 1.0) * texture(kd_texture, fs_in.tex_coord);
}

vec3 calc_light(vec3 normal, vec3 light_dir, vec3 light_color, vec3 view_dir)
{
    //diffuse lighting
    float diff = max(0.0, dot(normal, light_dir));
    
    //specular lighting
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(0.0, dot(view_dir, reflect_dir)), specular_exponent);

    vec3 diffuse = light_color * diff * kd;
    vec3 specular = light_color * spec * ks;
    return (diffuse + specular);
}

/*vec3 calc_light(vec3 mat_diffuse, vec3 mat_specular, vec3 normal, vec3 light_dir, vec3 light_color, vec3 view_dir)
{
    //diffuse lighting
    float diff = max(0.0, dot(normal, light_dir));
    
    //specular lighting
    vec3 reflectDir = reflect(-light_dir, normal);
    float spec = pow(max(0.0, dot(view_dir, reflect_dir)), specular_exponent);

    vec3 diffuse = light_color * diff * mat_diffuse * kd;
    vec3 specular = light_color * spec * mat_specular;
    return (diffuse + specular);
}*/




/* =================| old |====================


	vec3 temp_color = vec3(0, 0, 0);

	vec3 normal = normalize(fs_in.normal);

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
			light_dir = normalize(light_pos_dir[i] - fs_in.fragment_position);
			float constant = light_attenuation_params[i].x;
 			float linear = light_attenuation_params[i].y;	
 			float quadratic = light_attenuation_params[i].z;

			float distance = distance(light_pos_dir[i], fs_in.fragment_position);
			attenuation = 1.0 / (constant + linear * distance + quadratic * pow(distance, 2));
		}
		
		// Diffuse
		float diffuse = max(dot(normal, light_dir), 0.0);
		vec3 diffuse_light = kd * diffuse * light_color[i];

		// Specular
		vec3 view_dir = normalize(camera_pos - fs_in.fragment_position);
		vec3 reflection = reflect(-light_dir, normal);
		float specular = max(dot(reflection, view_dir), 0.0);

		vec3 specular_light = vec3(0,0,0);
		if(use_specularity_map)
		{
			vec3 spec_map = texture(specularity_map, fs_in.tex_coord).rgb;
			specular_light = ks * pow(specular, specular_exponent) * spec_map * light_color[i];
		}
		else
		{
			specular_light = ks * pow(specular, specular_exponent) * light_color[i];
		}

		temp_color += (diffuse_light + specular_light) * attenuation;
	}

	temp_color +=  ka / 5;

	vec4 tex = texture(kd_texture, fs_in.tex_coord);
	out_color = vec4(temp_color, 1.0) * tex;

	*/