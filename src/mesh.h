#pragma once

#include <glm/glm.hpp>
#import <iostream>
#include "buffers/buffers.h"
#include "shader.h"


class Mesh {
public:
    Mesh(const std::string& object_file_name,
         glm::vec3 position = glm::vec3(0.0f),
         glm::vec3 scale = glm::vec3(1.0f));

    std::shared_ptr<IndexBuffer> ibo;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<BufferLayout> layout;

    glm::vec3 m_position;
    glm::vec3 m_scale;

    // number of faces of triangles in the mesh
    unsigned int n_faces = 0;

    // material
    glm::vec3 m_ambient = glm::vec3(0);
    glm::vec3 m_diffuse = glm::vec3(0);
    glm::vec3 m_specular = glm::vec3(0);
    float m_shininess = 1.0f;
    unsigned int m_texture = 0;
};
