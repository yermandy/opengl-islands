#include <cstdint>

#include "vertex_buffer.h"
#include "logger.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
    LOG(glGenBuffers(1, &m_buffer_id));
    LOG(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id));
    LOG(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(uint32_t size, uint32_t stride) {
    m_size = size;
    m_stride = stride;
    LOG(glGenBuffers(1, &m_buffer_id));
    LOG(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id));
    glBufferData(GL_ARRAY_BUFFER, stride * size, nullptr, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    LOG(glDeleteBuffers(1, &m_buffer_id));
}

void VertexBuffer::Bind() const {
    LOG(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id));
}

void VertexBuffer::Unbind() const {
    LOG(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Push(const void* data, unsigned int offset) {
    LOG(glBufferSubData(GL_ARRAY_BUFFER, m_offset * m_size, offset * m_size, data));
    m_offset += offset;
}