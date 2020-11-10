#include "Model_Shader.h"

Model_Shader::Model_Shader()
    : Shader{"model.vert", "model.frag"}
{
    location_model_matrix = get_uniform_location("model_matrix");

    location_camera_pos = get_uniform_location("camera_pos");
    location_light_pos_dir = get_uniform_location("light_pos_dir");
    location_light_color = get_uniform_location("light_color");
    location_light_attenuation_params = get_uniform_location("light_attenuation_params");
    location_light_type = get_uniform_location("light_type");
    location_num_of_lights = get_uniform_location("number_of_lights");

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

void Model_Shader::load_lights(Light_Container const& light_container) const
{
    load_vec3_arr(location_light_pos_dir, light_container.get_pos_dir_data());
    load_vec3_arr(location_light_color, light_container.get_color_data());
    load_vec3_arr(location_light_attenuation_params, light_container.get_attenuation_data());
    load_bool_arr(location_light_type, light_container.get_light_type_data());
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