#pragma once

#include "vertex_buffer.h"

class BufferLayout;

class VertexArray {

private:

    unsigned int m_buffer_id{};

public:

    VertexArray();

    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout, uint32_t count_per_offset = 1);

    void Bind() const;

    void Unbind() const;

};