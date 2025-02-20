#pragma once

#ifdef WIN32
    #include "glad/glad.h"
#else
    #include "GL/gl.h"
#endif

#include "Vector.h"
#include "Matrix.h"
#include "Model_Shader.h"
#include "model_util.h"

#include <vector>
#include <string>
#include <map>

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
    Model(model::Vao_Data const& vao_data);
    ~Model();

    void update(float delta_time);
    virtual void render(Model_Shader const * shader) const;

    void set_position(vec3 const& new_pos) { position = new_pos; }
    void set_scale(vec3 const& new_scale) { scale = new_scale; }
    void set_rotation(vec3 const& new_rot) { rotation = new_rot; }

    Matrix4 const get_model_matrix() const;

    model::Material get_material() const;

protected:

    model::Vao_Data model_data {};

    vec3 position {};
    vec3 scale {1, 1, 1};
    vec3 rotation {};

private:

    //For model handler
    inline static std::map<std::string, model::Vao_Data> models {};
    void load_model(std::string const& file_name);
};
