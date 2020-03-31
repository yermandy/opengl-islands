#pragma once

#include "shader.h"
#include "buffers/buffers.h"

class Renderer {
public:
    void Clear() const;

    void DrawTriangles(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;

    void DrawLines(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
};