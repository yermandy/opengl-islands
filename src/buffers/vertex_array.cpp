#include "logger.h"
#include "vertex_array.h"
#include "buffer_layout.h"


VertexArray::VertexArray() {
    LOG(glGenVertexArrays(1, &m_renderer_id));
}

VertexArray::~VertexArray() {
    LOG(glDeleteVertexArrays(1, &m_renderer_id));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& layout) {
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    uint32_t offset = 0;
    for (uint32_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        LOG(glEnableVertexAttribArray(i));
        LOG(glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                     layout.GetStride(), (const void*) offset));
        offset += element.count * BufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const {
    LOG(glBindVertexArray(m_renderer_id));
}

void VertexArray::Unbind() const {
    LOG(glBindVertexArray(0));
}
