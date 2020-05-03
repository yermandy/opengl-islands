#include "common.h"

/*
 *
 * NOTE: Does not work now. Do not use this constructor!
 *
 */

Shape::Shape(const float* data, const unsigned int* indices, const std::initializer_list<unsigned int>& layout_shape) {
    vbo = std::shared_ptr<VertexBuffer>::make_shared(*new VertexBuffer(data, sizeof(data)));

    layout = std::shared_ptr<BufferLayout>::make_shared(*new BufferLayout());
    for (auto shape : layout_shape) {
        layout->Push(GL_FLOAT, shape, GL_FALSE);
    }

    vao = std::shared_ptr<VertexArray>::make_shared(*new VertexArray());
    vao->AddBuffer(*vbo, *layout);

    ibo = std::shared_ptr<IndexBuffer>::make_shared(*new IndexBuffer(indices, sizeof(indices)));
}

Shape::Shape() {}
