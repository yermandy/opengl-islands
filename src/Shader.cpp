#include "logger.h"
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& filepath)
        : m_file_path(filepath), m_renderer_id(0) {
    std::cout << "Loading shader : " << m_file_path << std::endl;
    ShaderProgramSource source = ParseShader(filepath);
    m_renderer_id = CreateShader(source.VertexSource, source.FragmentSource);
    Unbind();
}

Shader::~Shader() {
    LOG(glDeleteProgram(m_renderer_id));
}

void Shader::Bind() const {
    LOG(glUseProgram(m_renderer_id));
}

void Shader::Unbind() const {
    LOG(glUseProgram(0));
}

void Shader::SetInt1(const std::string& name, const int value) {
    LOG(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetFloat1(const std::string& name, const float v0) {
    LOG(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetFloat4(const std::string& name, const float v0, const float v1, const float v2, const float v3) {
    LOG(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetVec3(const std::string& name, const glm::vec3(vec3)) {
    LOG(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec3)));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) {
    LOG(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetMeshMaterial(const Mesh& mesh) {
    SetVec3("u_material.ambient", mesh.m_ambient);
    SetVec3("u_material.diffuse", mesh.m_diffuse);
    SetVec3("u_material.specular", mesh.m_specular);
    SetFloat1("u_material.shininess", mesh.m_shininess);
}

int Shader::GetUniformLocation(const std::string& name) const {
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
        return m_uniform_location_cache[name];
    LOG(int location = glGetUniformLocation(m_renderer_id, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " does not exist!" << std::endl;
    m_uniform_location_cache[name] = location;
    return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
//        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;

}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) const {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[int(type)] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::SetMVP(const glm::mat4& MVP, const glm::mat4& M, const glm::mat4& V) {
    SetMat4("u_MVP", MVP);
    SetMat4("u_M", M);
    SetMat4("u_V", V);
}


