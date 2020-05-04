#pragma once

#include <shader.h>

class Skybox {
public:
    Skybox();

    void BindTexture() const;

    void Draw() const;

    void ChangeSkybox();

    std::shared_ptr<Shader> shader;

private:
    unsigned int m_cube_map_texture_day_id{};
    unsigned int m_cube_map_texture_night_id{};
    unsigned int m_vao{}, m_ibo{};
    bool m_is_day = true;
};
