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

struct SpotLight : Light {
    glm::vec3 m_direction;
    glm::vec3 m_position;
    float m_cut_off;
    float m_outer_cut_off;
    float m_exponent;
    bool m_on;

    float m_constant = 0.5f;
    float m_linear = 0.03f;
    float m_quadratic = 0.01f;

    SpotLight(const glm::vec3& ambient,
              const glm::vec3& diffuse,
              const glm::vec3& specular,
              const glm::vec3 direction,
              const glm::vec3 position,
              const float cut_off,
              const float outer_cut_off,
              const float exponent,
              const bool on) :
            Light(ambient, diffuse, specular),
            m_direction(direction),
            m_position(position),
            m_cut_off(cut_off),
            m_outer_cut_off(outer_cut_off),
            m_exponent(exponent),
            m_on(on) {}
};