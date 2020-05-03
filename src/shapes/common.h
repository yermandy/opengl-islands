#pragma once

#include "buffers/buffers.h"

class Shape {
public:
    Shape(const float* data, const unsigned int* indices, const std::initializer_list<unsigned int>& layout_shape);

    std::shared_ptr<IndexBuffer> ibo;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<BufferLayout> layout;

protected:
    Shape();
};