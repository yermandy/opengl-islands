#pragma once

#include <vector>
#include <glm/glm.hpp>

class Hermite {
public:
//    Hermite(std::vector<glm::vec3>& control_points);
    Hermite(const std::initializer_list<glm::vec3>& control_points);

    glm::vec3 CalculatePosition(float t);

private:
    std::vector<glm::vec3> m_control_points;
    unsigned int m_size = 0;
};
