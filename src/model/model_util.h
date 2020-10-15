#pragma once

#include <string>
#include <iostream>

#include "glad/glad.h"
#include "stb_image.h"

inline unsigned int load_texture(std::string file_name, bool flip_y = true)
{
    unsigned int tex_id {0};

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip_y); // tell stb to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glGenTextures(1, &tex_id);
        glBindTexture(GL_TEXTURE_2D, tex_id);

        if (nrChannels == 3)
        {
            data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, STBI_rgb);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        //TODO: byt till att kasta ett undantag.
        std::cout << "Failed to load texture: " << file_name <<  std::endl;
    }
    stbi_image_free(data);

    return tex_id;
}