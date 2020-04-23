#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "mesh.h"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {

private:

    std::string m_file_path;
    unsigned int m_renderer_id;
    mutable std::unordered_map<std::string, int> m_uniform_location_cache;

public:

    Shader(const std::string& filepath);

    virtual ~Shader();

    void Bind() const;

    void Unbind() const;

    void SetInt1(const std::string& name, const int value);

    void SetFloat1(const std::string& name, const float value);

    void SetFloat4(const std::string& name, const float v0, const float v1, const float v2, const float v3);

    void SetVec3(const std::string& name, const glm::vec3(vec3));

    void SetMat4(const std::string& name, const glm::mat4& matrix);

    void SetMeshMaterial(const Mesh& mesh);

    void SetMVP(const glm::mat4& MVP, const glm::mat4& M, const glm::mat4& V);

private:

    int GetUniformLocation(const std::string& name) const;

    ShaderProgramSource ParseShader(const std::string& filepath) const;

    unsigned int CompileShader(unsigned int type, const std::string& source) const;

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;

};
