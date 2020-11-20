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
uniform sampler2D shadow_map;

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
float calc_shadow();

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

			float shadow = 0; //calc_shadow();
		
			output += (1 - shadow) * calc_light(normal, light_dir, light_color[i], view_dir);
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

float calc_shadow()
{
    /*float offset = 0.0004;

    // perform perspective divide
    vec3 proj_coords = fs_in.fragment_position_light_space.xyz / fs_in.fragment_position_light_space.w;

    // transform to [0,1] range
    proj_coords = proj_coords * 0.5 + 0.5;

    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closest_depth = texture(shadow_map, proj_coords.xy).r; 

    // get depth of current fragment from light's perspective
    float current_depth = proj_coords.z;

    // check whether current frag pos is in shadow
    float shadow = 0.0;
    vec2 texel_size = 1.0 / textureSize(shadow_map, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcf_depth = texture(shadow_map, proj_coords.xy + vec2(x, y) * texel_size).r; 
            shadow += current_depth - offset > pcf_depth ? 1.0 : 0.0;        
        }
    }
    shadow /= 9.0;

    return shadow;*/


	// perform perspective divide
    vec3 projCoords = fs_in.fragment_position_light_space.xyz / fs_in.fragment_position_light_space.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadow_map, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}
