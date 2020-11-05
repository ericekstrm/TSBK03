#pragma once

#include "glad/glad.h"
#include "Vector.h"
#include "Matrix.h"
#include "OBJ_Loader.h"
#include "Shader.h"

#include <vector>
#include <string>
#include <map>

class Model_Shader;

class Model
{
public:
    Model();
    Model(std::string const& file_name, vec3 const& position = {0, 0, 0});
    Model(std::vector<float> vertices, 
        std::vector<float> normals, 
        std::vector<float> texture_coords, 
        std::vector<int> indices,
        objl::Material material);
    ~Model();

    void update(float delta_time);
    virtual void render(Model_Shader const& shader) const;

    void set_position(vec3 const& new_pos) { position = new_pos; }
    void set_scale(vec3 const& new_scale) { scale = new_scale; }
    void set_rotation(vec3 const& new_rot) { rotation = new_rot; }

    Matrix4 const get_model_matrix() const;

    struct Material
    {
        unsigned int texture_id {};
        unsigned int specularity_map_id {};
        bool use_specularity_map {};
        vec3 ka {};
        vec3 kd {};
        vec3 ks {};
        float a {};
    };

    struct Model_Data
    {
        void load_buffer_data(std::vector<float> const&, std::vector<float> const&, std::vector<float> const&, std::vector<int> const&);
        void reload_buffer_data(std::vector<float> const&, std::vector<float> const&, std::vector<float> const&, std::vector<int> const&);
        unsigned int vao {};
        unsigned int vb {}, nb {}, tb {}, ib {};
        unsigned int indices_count {};
        Material material {};
    };

    Material get_material() const;

protected:

    Model_Data model_data {};

    vec3 position {};
    vec3 scale {1, 1, 1};
    vec3 rotation {};

private:

    //For model handler
    inline static std::map<std::string, Model_Data> models {};
    void load_model(std::string const& file_name);
    Model_Data load_model_from_file(std::string const& file_name) const;
};

struct Buffer_Data_Struct
{
    std::vector<float> vertices {};
    std::vector<float> normals {};
    std::vector<float> texture_coords {};
    std::vector<int> indices {};
};