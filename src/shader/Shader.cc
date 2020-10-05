#include "Shader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <iterator>

Shader::Shader()
    : Shader("pass.vert", "pass.frag")
{
}

Shader::Shader(std::string const& vertex_file, std::string const& fragment_file)
{
    vertexID = load(vertex_file, GL_VERTEX_SHADER);
    fragmentID = load(fragment_file, GL_FRAGMENT_SHADER);
    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    location_projection_matrix = get_uniform_location("projection");
    location_camera_matrix = get_uniform_location("camera_matrix");
}

Shader::~Shader()
{
}

void Shader::start() const
{
    glUseProgram(programID);
}

void Shader::stop() const
{
    glUseProgram(0);
}

int Shader::get_uniform_location(std::string const& uniform_name) const
{
    const GLchar* c = uniform_name.c_str();
    return glGetUniformLocation(programID, c);
}

void Shader::load_int(int location, int value) const
{
    glUniform1i(location, value);
}

void Shader::load_float(int location, float value) const
{
    glUniform1f(location, value);
}

void Shader::load_bool(int location, bool b) const
{
    glUniform1i(location, b ? 1 : 0);
}

void Shader::load_mat4(int location, mat4 const& value) const
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &value.transpose().m[0][0]);
}

void Shader::load_vec3(int location, vec3 const& value) const
{
    glUniform3f(location, value[0], value[1], value[2]);
}

void Shader::load_vec4(int location, vec4 const& value) const
{
    glUniform4f(location, value[0], value[1], value[2], value[3]);
}

void Shader::load_bool_arr(int location, std::vector<int> const& value) const
{
    glUniform1iv(location, value.size(), reinterpret_cast<const int *>(value.data()));
}

void Shader::load_vec3_arr(int location, std::vector<vec3> const& value) const
{
    // undrar om detta fungerar som man väntar sig, inte helt säkert eftersom vi har min egen vec3.
    // Det fungerar med Ingemars vec3 men det är ju verkligen inte en garanti att det fungerar senare, hehe.
    glUniform3fv(location, value.size(), reinterpret_cast<const float *>(value.data()));
}

int Shader::get_programID() const
{
    return programID;
}

void Shader::load_projection_matrix(Matrix4 const& mat) const
{
    load_mat4(location_projection_matrix, mat);
}

void Shader::load_camera_matrix(Matrix4 const & mat) const
{
    load_mat4(location_camera_matrix, mat);
}

int Shader::load(std::string const & file_name, int type)
{
    std::ifstream shader_source {"res/shader_files/" + file_name};
    if (!shader_source.is_open())
    {
        std::cerr << "Shader file not found: " << file_name << std::endl;
        return 0;
    }

    // now read in the data
    std::string str_source = std::string((std::istreambuf_iterator<char>(shader_source)), std::istreambuf_iterator<char>());
    shader_source.close();
    str_source += "\0";

    int shaderID = glCreateShader(type);

    const char* data = str_source.c_str();
    glShaderSource(shaderID, 1, &data, NULL);
    glCompileShader(shaderID);

    int is_compiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

        std::copy(errorLog.begin(), errorLog.end(), std::ostream_iterator<GLchar> {std::cerr});
    }
    return shaderID;
}

//=======================
//===| Skybox Shader |===
//=======================

Skybox_Shader::Skybox_Shader()
    : Shader {"skybox.vert", "skybox.frag"}
{
}

//======================
//===| Model Shader |===
//======================

Model_Shader::Model_Shader()
    : Shader{"test.vert", "test.frag"}
{
    
    location_kd_texture = get_uniform_location("kd_texture");
    location_world_matrix = get_uniform_location("world_matrix");

    connect_texture_units();
}

Model_Shader::~Model_Shader()
{
}

//loads the texture to a specific texture unit
void Model_Shader::connect_texture_units() const
{
    load_int(location_kd_texture, 0);
}

void Model_Shader::load_world_matrix(Matrix4 const & mat) const
{
    load_mat4(location_world_matrix, mat);
}
