#include "curve.h"

#include <glm/gtx/spline.hpp>

Hermite::Hermite(const std::initializer_list<glm::vec3>& control_points) {
    for (auto point : control_points) {
        m_control_points.push_back(point);
    }
}

glm::vec3 Hermite::CalculatePosition(float t) {
    int t_i = (int(t) % 4) * 2;
    return glm::hermite(m_control_points[0 + t_i],
                        m_control_points[1 + t_i],
                        m_control_points[2 + t_i],
                        m_control_points[3 + t_i],
                        glm::mod(t, 1.0f));
}
