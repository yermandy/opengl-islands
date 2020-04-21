#pragma once

#include <string>

class Texture {
private:
//    unsigned int m_texture_id;
    std::string m_file_path;
    char* m_buffer;
    int m_width, m_height, m_BPP;
public:
    unsigned int m_texture_id;
    explicit Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind(unsigned int slot = 0) const;

    [[nodiscard]] inline int GetWidth() const {return m_width;};
    [[nodiscard]] inline int GetHeight() const {return m_height;};

};