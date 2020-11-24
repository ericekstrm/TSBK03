#include "Sun.h"

Sun::Sun()
    : Dir_Light(vec3{0,1,0}, vec3{1,1,1})
{
}

Sun::~Sun()
{

}

void Sun::render(Camera const& camera) const
{
    glDisable(GL_DEPTH_TEST);

    shader.start();
    shader.load_projection_matrix();
    shader.load_camera_matrix(camera.get_camera_matrix().remove_translation());
    shader.load_model_matrix(translation_matrix(pos) * rot); //TODO

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, billboard.material.texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindVertexArray(billboard.vao);
    glDrawElements(GL_TRIANGLES, billboard.indices_count, GL_UNSIGNED_INT, 0);

    shader.stop();
    glEnable(GL_DEPTH_TEST);
}

void Sun::update(float delta_time)
{
    pos = rotation_matrix(delta_time / 2, vec3{0,0,1}) * pos;

    //rotate the sun so that it always faces its rotation center
    rot = rotation_matrix(vec3{0,0,1}, (pos * -1).normalize());
}