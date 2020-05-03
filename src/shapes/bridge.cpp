#include "bridge.h"

Bridge::Bridge() {
    vbo = std::shared_ptr<VertexBuffer>::make_shared(*new VertexBuffer(m_data, sizeof(m_data)));

    layout = std::shared_ptr<BufferLayout>::make_shared(*new BufferLayout());
    layout->Push(GL_FLOAT, 3, GL_FALSE);
    layout->Push(GL_FLOAT, 3, GL_FALSE);
    layout->Push(GL_FLOAT, 2, GL_FALSE);

    vao = std::shared_ptr<VertexArray>::make_shared(*new VertexArray());
    vao->AddBuffer(*vbo, *layout);

    ibo = std::shared_ptr<IndexBuffer>::make_shared(*new IndexBuffer(m_indices, sizeof(m_indices)));
}

