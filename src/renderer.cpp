#include "renderer.h"
#include "logger.h"

void Renderer::Clear() const {
    LOG(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawTriangles(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const {
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    LOG(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawLines(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const {
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    LOG(glDrawElements(GL_LINES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}
