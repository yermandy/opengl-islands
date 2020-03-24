#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

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

    void SetUniform1i(const std::string& name, int value);

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:

    int GetUniformLocation(const std::string& name) const;

    ShaderProgramSource ParseShader(const std::string& filepath) const;

    unsigned int CompileShader(unsigned int type, const std::string& source) const;

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;

};
