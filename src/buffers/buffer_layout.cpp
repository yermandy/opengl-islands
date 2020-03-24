#include "buffer_layout.h"

unsigned int BufferElement::GetSizeOfType(const uint32_t type) {
    switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
    }
    ASSERT(false);
    return 0;
}

void BufferLayout::Push(const uint32_t type, const uint32_t count, const uint32_t normalized) {
    m_elements.push_back({type, count, normalized});
    m_stride += BufferElement::GetSizeOfType(type) * count;
}
