#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Matrix.h"

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
    int location_camera_matrix;
};

class Skybox_Shader : public Shader
{
public:
    Skybox_Shader();

private:

};

class Model_Shader : public Shader
{
public:
    Model_Shader();
    ~Model_Shader();

    void load_world_matrix(Matrix4 const& mat) const;

private:

    void connect_texture_units() const;

    int location_kd_texture;

    int location_world_matrix;
};
