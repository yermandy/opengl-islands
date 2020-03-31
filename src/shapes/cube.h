#pragma once

#include "buffers/buffers.h"

class Cube {

public:
    Cube();
    virtual ~Cube();

    std::shared_ptr<IndexBuffer> ibo;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<BufferLayout> layout;
};