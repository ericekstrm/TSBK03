#pragma once

#include "Shader.h"
#include "Light.h"

class Model_Shader : public Shader
{
public:
    Model_Shader();
    Model_Shader(std::string const& vertex_file, std::string const& fragment_file);
    ~Model_Shader();

    void load_model_matrix(Matrix4 const& mat) const;

    void load_camera_position  (vec3 const& camera_pos) const;
    void load_lights(Light_Container const& light_container) const;
    void load_material_properties(model::Material const& mat) const;

private:

    void connect_texture_units() const;

    int location_model_matrix;

    // Material 
    int location_kd_texture;
    int location_specularity_map;
    int location_use_specularity_map;
    int location_ka;
    int location_kd;
    int location_ks;
    int location_a;

    int location_camera_pos;

    // Light
    int location_num_of_lights;
    int location_light_pos_dir;
    int location_light_color;
    int location_light_attenuation_params;
    int location_light_type;
};
