#include "Model_Shader.h"

#include <algorithm>

Model_Shader::Model_Shader()
    : Model_Shader{"model.vert", "model.frag"}
{
}

Model_Shader::Model_Shader(std::string const& vertex_file, std::string const& fragment_file)
    : Shader{vertex_file, fragment_file}
{
    location_model_matrix = get_uniform_location("model_matrix");

    location_camera_pos = get_uniform_location("camera_pos");
    location_num_of_lights = get_uniform_location("number_of_lights");

    location_light_pos_dir = get_uniform_location("light_pos_dir");
    location_light_color = get_uniform_location("light_color");
    location_light_attenuation_params = get_uniform_location("light_attenuation_params");
    location_light_type = get_uniform_location("light_type");

    /*for (int i = 0; i < MAX_LIGHTS; i++)
    {
        location_pos_light_position[i] = get_uniform_location("pos_lights[" + std::to_string(i) + "].position");
        location_pos_light_color[i] = get_uniform_location("pos_lights[" + std::to_string(i) + "].color");
        location_pos_light_attenuation_constant[i] = get_uniform_location("pos_lights[" + std::to_string(i) + "].attenuation_constant");
        location_pos_light_attenuation_linear[i] = get_uniform_location("pos_lights[" + std::to_string(i) + "].attenuation_linear");
        location_pos_light_attenuation_quadratic[i] = get_uniform_location("pos_lights[" + std::to_string(i) + "].attenuation_quadratic");

        location_dir_light_direction[i] = get_uniform_location("dir_lights[" + std::to_string(i) + "].direction");
        location_dir_light_color[i] = get_uniform_location("dir_lights[" + std::to_string(i) + "].color");
    }*/

    location_kd_texture = get_uniform_location("kd_texture");
    location_specularity_map = get_uniform_location("specularity_map");
    location_use_specularity_map = get_uniform_location("use_specularity_map");
    location_ka = get_uniform_location("ka");
    location_kd = get_uniform_location("kd");
    location_ks = get_uniform_location("ks");
    location_a = get_uniform_location("a");

    connect_texture_units();
}

Model_Shader::~Model_Shader()
{
}

//loads the texture to a specific texture unit
void Model_Shader::connect_texture_units() const
{
    load_int(location_kd_texture, 0);
    load_int(location_specularity_map, 1);
}

void Model_Shader::load_model_matrix(Matrix4 const& mat) const
{
    load_mat4(location_model_matrix, mat);
}

void Model_Shader::load_camera_position(vec3 const& camera_pos) const
{
    load_vec3(location_camera_pos, camera_pos);
}

//std::size_t Model_Shader::MAX_LIGHTS = 10;

void Model_Shader::load_lights(Light_Container const& light_container) const
{
    load_vec3_arr(location_light_pos_dir, light_container.get_pos_dir_data());
    load_vec3_arr(location_light_color, light_container.get_color_data());
    load_vec3_arr(location_light_attenuation_params, light_container.get_attenuation_data());
    load_bool_arr(location_light_type, light_container.get_light_type_data());

    /*std::vector<Pos_Light> const& pos_lights {light_container.get_pos_lights()};
    std::vector<Dir_Light> const& dir_lights {light_container.get_dir_lights()};

    for (unsigned i = 0; i < std::max(MAX_LIGHTS, pos_lights.size()); i++)
    {
        load_vec3(location_pos_light_position[i], pos_lights[i].get_position()); 
        load_vec3(location_pos_light_color[i], pos_lights[i].get_color());
        load_float(location_pos_light_attenuation_constant[i], pos_lights[i].get_attenuation_constant());
        load_float(location_pos_light_attenuation_linear[i], pos_lights[i].get_attenuation_linear());
        load_float(location_pos_light_attenuation_quadratic[i], pos_lights[i].get_attenuation_quadratic());
    }

    for (unsigned i = 0; i < std::max(MAX_LIGHTS, dir_lights.size()); i++)
    {
        load_vec3(location_dir_light_direction[i], dir_lights[i].get_direction());
        load_vec3(location_dir_light_color[i], dir_lights[i].get_color());
    }*/

    load_int(location_num_of_lights, light_container.get_number_of_lights());
}

void Model_Shader::load_material_properties(model::Material const& mat) const
{
    load_vec3(location_ka, mat.ka);
    load_vec3(location_kd, mat.kd);
    load_vec3(location_ks, mat.ks);
    load_float(location_a, mat.a);
    load_bool(location_use_specularity_map, mat.use_specularity_map);
}