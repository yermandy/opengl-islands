#include "skybox.h"
#include <vector>
#include <stb_image/stb_image.h>
#include <GL/glew.h>
#include <iostream>

unsigned int LoadCubeMap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // unbind the texture (just in case someone will mess up with texture calls later)
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return textureID;
}

Skybox::Skybox() {
    std::vector<std::string> faces{
            "res/textures/skybox/night/left.png",
            "res/textures/skybox/night/right.png",
            "res/textures/skybox/night/bottom.png",
            "res/textures/skybox/night/top.png",
            "res/textures/skybox/night/front.png",
            "res/textures/skybox/night/back.png",
    };

    m_cube_map_texture_id = LoadCubeMap(faces);

    static const float screenCoords[] = {
            -1.0f, -1.0f,
             1.0f, -1.0f,
            -1.0f, 1.0f,
             1.0f, 1.0f
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_ibo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenCoords), &screenCoords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    shader = std::make_shared<Shader>(*new Shader("res/shaders/skybox.shader"));
}

void Skybox::Draw() const {
    // change depth function so depth test passes when values are equal to depth buffer's content
    glDepthFunc(GL_LEQUAL);
    // bind geometry
    glBindVertexArray(m_vao);
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cube_map_texture_id);
    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    // set depth function back to default
    glDepthFunc(GL_LESS);
}
