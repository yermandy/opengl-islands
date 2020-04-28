#include "cube.h"


Cube::Cube() {

    vbo = std::shared_ptr<VertexBuffer>::make_shared(*new VertexBuffer(m_cube_data, sizeof(m_cube_data)));

    layout = std::shared_ptr<BufferLayout>::make_shared(*new BufferLayout());
    layout->Push(GL_FLOAT, 3, GL_FALSE);
    layout->Push(GL_FLOAT, 3, GL_FALSE);

    vao = std::shared_ptr<VertexArray>::make_shared(*new VertexArray());
    vao->AddBuffer(*vbo, *layout);

    ibo = std::shared_ptr<IndexBuffer>::make_shared(*new IndexBuffer(m_cube_indices, sizeof(m_cube_indices)));
}

Cube::~Cube() = default;
