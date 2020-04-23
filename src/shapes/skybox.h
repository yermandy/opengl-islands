#pragma once

#include <shader.h>

class Skybox {
public:
    Skybox();

    void Draw() const;

    std::shared_ptr<Shader> shader;

private:
    unsigned int m_cube_map_texture_id{};
    unsigned int m_vao{}, m_ibo{};
};
