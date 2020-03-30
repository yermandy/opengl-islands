#pragma once

#include "shader.h"
#include "buffers/buffers.h"

class Renderer {
public:
    void Clear() const;

    void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
};