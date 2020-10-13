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
    Model(std::string const& file_name, vec3 const& position);
    ~Model();

    void update(float delta_time);
    virtual void render(Model_Shader const& shader) const;

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
        unsigned int vao {};
        unsigned int vb {}, nb {}, tb {}, ib {};
        unsigned int indices_count {};
        Material material {};
    };

    Material get_material() const;

protected:
    //void load_buffer_data(std::vector<float> const&, std::vector<float> const&, std::vector<int> const&);
    unsigned int load_texture(std::string file_name) const;

    Model_Data model_data {};

private:

    Model(std::vector<float> vertices, 
          std::vector<float> normals, 
          std::vector<float> texture_coords, 
          std::vector<int> indices,
          objl::Material material);

    vec3 position {};
    vec3 scale {1, 1, 1};
    vec3 rotation {};

//For model handler
    inline static std::map<std::string, Model_Data> models {};
    void load_model(std::string const& file_name);
    Model_Data load_model_from_file(std::string const& file_name) const;

};
