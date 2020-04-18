#pragma once

#include <glm/glm.hpp>

struct Light {

    Light(const glm::vec3& ambient,
          const glm::vec3& diffuse,
          const glm::vec3& specular) :
            m_ambient(ambient),
            m_diffuse(diffuse),
            m_specular(specular) {}

    glm::vec3 m_ambient = glm::vec3(0);
    glm::vec3 m_diffuse = glm::vec3(0);
    glm::vec3 m_specular = glm::vec3(0);
};

struct PointLight : Light {
    glm::vec3 m_position;

    float m_constant;
    float m_linear;
    float m_quadratic;

    PointLight(const glm::vec3& ambient,
               const glm::vec3& diffuse,
               const glm::vec3& specular,
               const glm::vec3 position,
               const float constant = 1.0f,
               const float linear = 0.0f,
               const float quadratic = 0.0f) :
            Light(ambient, diffuse, specular),
            m_position(position),
            m_constant(constant),
            m_linear(linear),
            m_quadratic(quadratic) {}
};

struct DirectionalLight : Light {
    glm::vec3 m_direction;

    DirectionalLight(const glm::vec3& ambient,
               const glm::vec3& diffuse,
               const glm::vec3& specular,
               const glm::vec3 direction) :
            Light(ambient, diffuse, specular),
            m_direction(direction) {}
};