#pragma once

class VertexBuffer {

private:

    unsigned int m_buffer_id{};
    unsigned int m_size = 0;
    unsigned int m_stride = 0;
    unsigned int m_offset = 0;

public:

    VertexBuffer(const void* data, uint32_t size);

    VertexBuffer(uint32_t size, uint32_t stride);

    virtual ~VertexBuffer();

    void Bind() const;

    void Unbind() const;

    void Push(const void* data, unsigned int offset);

};


