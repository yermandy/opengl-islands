#pragma once

class IndexBuffer {
private:
    unsigned int m_buffer_id{};
    unsigned int m_count;
public:

    IndexBuffer(const unsigned int* data, unsigned int size);

    virtual ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

    inline unsigned int GetCount() const { return m_count; }
};