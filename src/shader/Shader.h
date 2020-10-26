#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "Matrix.h"
#include "Model.h"
#include "Light.h"

class Model;

class Shader
{
public:
    Shader();
    Shader(std::string const& vertex_file, std::string const& fragment_file);
    virtual ~Shader();

    void start() const;
    void stop() const;

    int get_programID() const;

    void load_projection_matrix(Matrix4 const& mat) const;
    void load_camera_matrix(Matrix4 const& mat) const;

protected:
    int get_uniform_location(std::string const& uniform_name) const;

    void load_int  (int location, int         value) const;
    void load_float(int location, float       value) const;
    void load_bool (int location, bool        value) const;
    void load_mat4 (int location, mat4 const& value) const;
    void load_vec3 (int location, vec3 const& value) const;
    void load_vec4 (int location, vec4 const& value) const;
    
    void load_vec3_arr(int location, std::vector<vec3> const& value) const;
    void load_bool_arr(int location, std::vector<int>  const& value) const;

private:

    int load(std::string const& file_name, int type);

    int programID {};
    int vertexID {};
    int fragmentID {};

    int location_projection_matrix;
    int location_world_matrix;
};

// =======================
// ===| Skybox Shader |===
// =======================

class Skybox_Shader : public Shader
{
public:
    Skybox_Shader();

private:

};

// ======================
// ===| Model Shader |===
// ======================

class Model_Shader : public Shader
{
public:
    Model_Shader();
    ~Model_Shader();

    void load_model_matrix(Matrix4 const& mat) const;

    void load_camera_position  (vec3 const& camera_pos) const;
    void load_lights(Light_Container const& light_container) const;
    void load_material_properties(Model const& obj) const;

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

// =====================
// ===| Tree Shader |===
// =====================

class Tree_Shader : public Shader
{
public:
    Tree_Shader();
    ~Tree_Shader();

    void load_model_matrix(Matrix4 const& mat) const;

private:
    int location_model_matrix;
};

// =====================
// ===| Text Shader |===
// =====================

class Text_Shader : public Shader
{
public:
    Text_Shader();
    ~Text_Shader();

    void load_font_color(vec3 const& color) const;
    void load_text_pos_matrix(Matrix4 const& mat) const;
    void load_char_pos_matrix(Matrix4 const& mat) const;

private:

    int location_font_color;
    int location_text_pos_matrix;
    int location_char_pos_matrix;
    int location_tex;
};

// ========================
// ===| Image2D Shader |===
// ========================

class Image2D_Shader : public Shader
{
public:
    Image2D_Shader();
    ~Image2D_Shader();

    void load_pos_matrix(vec2 const& pos) const;

private:

    int location_pos_matrix;
    int location_tex;
};