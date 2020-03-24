#pragma once

#include "vertex_buffer.h"

class BufferLayout;

class VertexArray {

private:

    unsigned int m_renderer_id;

public:

    VertexArray();

    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);

    void Bind() const;

    void Unbind() const;

};