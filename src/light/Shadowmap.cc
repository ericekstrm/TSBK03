#include "Shadowmap.h"

#include "settings.h"

#include <iostream>

Shadowmap::Shadowmap(vec3 const& light_position)
    : light_position {light_position}
{

    glGenFramebuffers(1, &depth_map_fbo);

    glGenTextures(1, &depth_map);
    glBindTexture(GL_TEXTURE_2D, depth_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "framebuffer not constructed correctly." << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadowmap::activate() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
    glViewport(0, 0, shadow_width, shadow_height);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Shadowmap::deactivate() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0, window_width, window_height);
}

void Shadowmap::render(Tree const& tree, Tree_Shader const& shader) const
{

    /*shader.start();
    shader.load_camera_matrix(look_at(light_position, vec3{0,0,0}, vec3{0,1,0}));
    shader.load_projection_matrix();
    //shader.load_light_space_matrix();

    tree.render(shader);

    shader.stop();*/
}

void Shadowmap::render(Terrain const& terrain) const
{

    shader.start();
    shader.load_light_space_matrix(light_position);

    terrain.render(&shader);

    shader.stop();
}

void Shadowmap::render(Model const& model) const
{

    shader.start();
    shader.load_light_space_matrix(light_position);

    model.render(&shader);

    shader.stop();
}
