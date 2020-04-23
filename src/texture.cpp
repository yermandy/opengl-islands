#include <GL/glew.h>
#include "logger.h"
#include "texture.h"
#include "stb_image/stb_image.h"
#include <iostream>
#include <sys/stat.h>

Texture::Texture(const std::string& path)
        : m_texture_id(0), m_buffer(nullptr), m_width(0), m_height(0), m_BPP(0) {

    struct stat buffer{};
    if (stat(path.c_str(), &buffer) != 0) {
        std::cerr << "Texture " << path << " does not exist" << std::endl;
        throw std::exception();
    }

    stbi_set_flip_vertically_on_load(1);
    m_buffer = reinterpret_cast<char*>(stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4));

    LOG(glGenTextures(1, &m_texture_id));
    LOG(glBindTexture(GL_TEXTURE_2D, m_texture_id));

    LOG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    LOG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    LOG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    LOG(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    LOG(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
    LOG(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_buffer) stbi_image_free(m_buffer);
    Unbind();
}

Texture::~Texture() {
    LOG(glDeleteTextures(1, &m_texture_id));
}

void Texture::Bind(unsigned int slot) const {
    LOG(glActiveTexture(GL_TEXTURE0 + slot));
    LOG(glBindTexture(GL_TEXTURE_2D, m_texture_id));

}

void Texture::Unbind(unsigned int slot) const {
    LOG(glBindTexture(GL_TEXTURE_2D, slot));
}
