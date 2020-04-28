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

    float m_cube_data[6 * 8] = {
//            x      y      z       r     g     b
            -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f, // 0
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 0.8f, // 1
            -1.0f,  1.0f, -1.0f,   0.0f, 0.8f, 0.0f, // 2
            -1.0f,  1.0f,  1.0f,   0.0f, 0.8f, 0.8f, // 3
             1.0f, -1.0f, -1.0f,   0.8f, 0.0f, 0.0f, // 4
             1.0f, -1.0f,  1.0f,   0.8f, 0.0f, 0.8f, // 5
             1.0f,  1.0f, -1.0f,   0.8f, 0.8f, 0.0f, // 6
             1.0f,  1.0f,  1.0f,   0.8f, 0.8f, 0.8f // 7
    };

    const unsigned int m_cube_indices[6 * 6] = {
            0, 2, 4,   4, 2, 6, // back face
            0, 1, 2,   2, 1, 3, // left face
            1, 5, 3,   3, 5, 7, // front face
            5, 4, 7,   7, 4, 6, // right face
            3, 7, 2,   2, 7, 6, // upper face
            0, 4, 1,   1, 4, 5, // lower face
    };
};