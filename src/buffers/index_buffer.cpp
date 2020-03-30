#include "index_buffer.h"
#include "logger.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
        : m_count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    LOG(glGenBuffers(1, &m_renderer_id));
    LOG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    LOG(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    LOG(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::Bind() const{
    LOG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::Unbind() const{
    LOG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}