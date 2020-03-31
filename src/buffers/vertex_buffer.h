#pragma once

class VertexBuffer {

private:

    unsigned int m_renderer_id{};

public:

    VertexBuffer(const void* data, uint32_t size);

    virtual ~VertexBuffer();

    void Bind() const;

    void Unbind() const;

};


