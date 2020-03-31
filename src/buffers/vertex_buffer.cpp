#include <cstdint>

#include "vertex_buffer.h"
#include "logger.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
    LOG(glGenBuffers(1, &m_renderer_id));
    LOG(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    LOG(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    LOG(glDeleteBuffers(1, &m_renderer_id));
}

void VertexBuffer::Bind() const {
    LOG(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void VertexBuffer::Unbind() const {
    LOG(glBindBuffer(GL_ARRAY_BUFFER, 0));
}