#include "Shader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <iterator>

#include "Vector.h"

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

    location_projection_matrix = get_uniform_location("projection_matrix");
    location_world_matrix = get_uniform_location("world_matrix");
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

//======================
//===| Model Shader |===
//======================

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

void Model_Shader::load_material_properties(Model const& obj) const
{
    auto mat = obj.get_material();

    load_vec3(location_ka, mat.ka);
    load_vec3(location_kd, mat.kd);
    load_vec3(location_ks, mat.ks);
    load_float(location_a, mat.a);
    load_bool(location_use_specularity_map, mat.use_specularity_map);
}

// =====================
// ===| Tree Shader |===
// =====================

Tree_Shader::Tree_Shader()
    : Shader{"tree.vert", "tree.frag"}
{
    location_model_matrix = get_uniform_location("model_matrix");
}

Tree_Shader::~Tree_Shader()
{
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
