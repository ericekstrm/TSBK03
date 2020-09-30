#include "Shader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <iterator>

Shader::Shader()
    : Shader("test.vert", "test.frag")
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

    get_all_uniform_locations();

    connect_texture_units();
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

void Shader::get_all_uniform_locations()
{
    location_tex = get_uniform_location("tex");

    location_projection_matrix = get_uniform_location("projection");
    location_camera_matrix = get_uniform_location("camera_matrix");
    location_world_matrix = get_uniform_location("world_matrix");
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

void Shader::load_matrix(int location, Matrix4 const& matrix) const
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.transpose().m[0][0]);
}

int Shader::get_programID() const
{
    return programID;
}

void Shader::load_projection_matrix(Matrix4 const& mat) const
{
    load_matrix(location_projection_matrix, mat);
}

void Shader::load_camera_matrix(Matrix4 const & mat) const
{
    load_matrix(location_camera_matrix, mat);
}

void Shader::load_world_matrix(Matrix4 const & mat) const
{
    load_matrix(location_world_matrix, mat);
}

void Shader::connect_texture_units() const
{
    load_int(location_tex, 0);
}

int Shader::load(std::string const & file_name, int type)
{
    std::ifstream shader_source {"res/shader_files/" + file_name};
    if (!shader_source.is_open())
    {
        std::cerr << " Shader file not found: " << file_name << std::endl;
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