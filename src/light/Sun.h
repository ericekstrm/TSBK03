#include "Light.h"
#include "model_util.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Vector.h"



class Sun : public Dir_Light
{
public:

    Sun();
    ~Sun();

    void render(Camera const& camera) const;
    void update(float delta_time);

    vec3 get_position() const { return pos; }

private:

    model::Vao_Data billboard {model::get_billboard("res/images/sun.png")};
    Billboard_Shader shader {};

    vec3 pos {5, 0, 0};
    mat4 rot {};
};