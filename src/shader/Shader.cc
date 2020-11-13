#include "Shader.h"

#ifdef WIN32
    #include "glad/glad.h"
#else
    #include "GL/gl.h"
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <iterator>

#include "Vector.h"

#include "settings.h"

Shader::Shader()
    : Shader("pass.vert", "pass.frag")
{
}

Shader::Shader(std::string const& vertex_file, std::string const& fragment_file)
{
    int vertexID = load(vertex_file, GL_VERTEX_SHADER);
    int fragmentID = load(fragment_file, GL_FRAGMENT_SHADER);
    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    location_projection_matrix = get_uniform_location("projection_matrix");
    location_world_matrix = get_uniform_location("world_matrix");
}

Shader::~Shader()
{
    glDeleteProgram(programID);
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
    mat4 tmp {value.transpose()};
    glUniformMatrix4fv(location, 1, GL_FALSE, &tmp.m[0][0]);
}

void Shader::load_vec3(int location, vec3 const& value) const
{
    glUniform3f(location, value.x, value.y, value.z);
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

void Shader::load_projection_matrix() const
{
    load_mat4(location_projection_matrix, projection);
}

void Shader::load_camera_matrix(Matrix4 const & mat) const
{
    load_mat4(location_world_matrix, mat);
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

// =====================
// ===| Tree Shader |===
// =====================

Tree_Shader::Tree_Shader()
    : Shader{"tree.vert", "tree.frag"}
{
    location_model_matrix = get_uniform_location("model_matrix");
    location_kd_texture = get_uniform_location("kd_texture");

    connect_texture_units();
}

Tree_Shader::~Tree_Shader()
{
}

void Tree_Shader::connect_texture_units() const
{
    load_int(location_kd_texture, 0);
}

void Tree_Shader::load_model_matrix(Matrix4 const& mat) const
{
    load_mat4(location_model_matrix, mat);
}

// =====================
// ===| Text Shader |===
// =====================

Text_Shader::Text_Shader()
    : Shader{"text.vert", "text.frag"}
{
    location_font_color = get_uniform_location("font_color");
    location_text_pos_matrix = get_uniform_location("text_pos_matrix");
    location_char_pos_matrix = get_uniform_location("char_pos_matrix");

    location_tex = get_uniform_location("tex");
    load_int(location_tex, 0);
}

Text_Shader::~Text_Shader()
{
}

void Text_Shader::load_font_color(vec3 const& color) const
{
    load_vec3(location_font_color, color);
}

void Text_Shader::load_text_pos_matrix(Matrix4 const& mat) const
{
    load_mat4(location_text_pos_matrix, mat);
}

void Text_Shader::load_char_pos_matrix(Matrix4 const& mat) const
{
    load_mat4(location_char_pos_matrix, mat);
}

// ========================
// ===| Image2D Shader |===
// ========================

Image2D_Shader::Image2D_Shader()
    : Shader{"image2d.vert", "image2d.frag"}
{
    location_pos_matrix = get_uniform_location("pos_matrix");

    location_tex = get_uniform_location("tex");
    load_int(location_tex, 0);
}

Image2D_Shader::~Image2D_Shader()
{
}

void Image2D_Shader::load_pos_matrix(vec2 const& pos) const
{
    load_mat4(location_pos_matrix, translation_matrix(pos.x, pos.y, 0));
}

// ========================
// ===| Image2D Shader |===
// ========================

Color_Point_Shader::Color_Point_Shader()
    : Shader {"color_point.vert", "color_point.frag"}
{
    location_position = get_uniform_location("position");
    location_color = get_uniform_location("color");
}

void Color_Point_Shader::load_position(vec3 const& pos) const
{
    load_vec3(location_position, pos);
}

void Color_Point_Shader::load_color(vec3 const& color) const
{
    load_vec3(location_color, color);
}