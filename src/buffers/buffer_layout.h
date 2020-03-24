#pragma once

#include "logger.h"
#include "vector"

struct BufferElement {

    const unsigned int type;
    const unsigned int count;
    const unsigned int normalized;

    static unsigned int GetSizeOfType(uint32_t type);
};

class BufferLayout {
private:

    std::vector<BufferElement> m_elements;
    unsigned int m_stride;

public:
    BufferLayout() : m_stride(0) {};

    void Push(uint32_t type, uint32_t count, uint32_t normalized);

    inline const std::vector<BufferElement>& GetElements() const { return m_elements; }

    inline uint32_t GetStride() const { return m_stride; }
};
