#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "Matrix.h"
#include "model_util.h"

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

// =====================
// ===| Tree Shader |===
// =====================

class Tree_Shader : public Shader
{
public:
    Tree_Shader();
    ~Tree_Shader();

    void connect_texture_units() const;

    void load_model_matrix(Matrix4 const& mat) const;

private:
    int location_model_matrix;

    int location_kd_texture;
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

class Color_Point_Shader : public Shader
{
public:
    Color_Point_Shader();
    void load_position(vec3 const& pos) const;
    void load_color(vec3 const& color) const;

private:
    int location_position;
    int location_color;
};