#include "camera.h"

#include <iostream>
#include <glm/gtx/spline.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

std::vector<glm::vec3> control_points;

Camera::Camera(GLFWwindow* window) : m_window(window) {
    if (window == nullptr) {
        std::cerr << "Use GLFWwindow to initialize camera" << std::endl;
        return;
    }
    int w, h;
    glfwGetWindowSize(m_window, &w, &h);
    m_width = float(w);
    m_height = float(h);
    glfwPollEvents();
    glfwSetCursorPos(m_window, m_width / 2, m_height / 2);

    control_points.emplace_back(0.0f, 12.5f, 18.0f);
    control_points.emplace_back(-12.5f, 19.5f, 12.5f);
    control_points.emplace_back(-14.0f, 23.5f, -5.5f);
    control_points.emplace_back(4.5f, 26.5f, -16.5f);
    control_points.emplace_back(20.5f, 18.5f, -6.0f);
    control_points.emplace_back(23.0f, 7.5f, 13.0f);
    control_points.emplace_back(0.0f, 12.5f, 18.0f);
    control_points.emplace_back(-12.5f, 19.5f, 12.5f);
    control_points.emplace_back(-14.0f, 23.5f, -5.5f);
}

Camera::~Camera() {
    delete s_instance;
}

void Camera::SetWidthHeight(float width, float height) {
    m_width = width;
    m_height = height;
}

void Camera::UpdateViewProjection() {
//    std::cout << m_width << " : " << m_height << std::endl;

    // glfwGetTime is called only once, the first time this function is called
    static double last_time = glfwGetTime();

    // Compute time difference between current and last frame
    double current_time = glfwGetTime();
    auto delta_time = float(current_time - last_time);

    if (m_camera_view_type == CameraViewType::DYNAMIC) {
        auto t = float(current_time / 3.0f);
        int t_i = int(t) % 6;
        glm::vec3 point = glm::catmullRom(control_points[0 + t_i], control_points[1 + t_i],
                                          control_points[2 + t_i], control_points[3 + t_i],
                                          glm::mod(t, 1.0f));

        m_position = point;

        m_vertical_angle = -glm::atan(m_position.y + 3.0f,
                                              glm::sqrt(glm::pow(m_position.x, 2.0f) +
                                                        glm::pow(m_position.z, 2.0f)));

        m_horizontal_angle = -3.14f + glm::atan(m_position.x, m_position.z);
    } else if (!m_main_menu) {
        // Get mouse position
        glfwGetCursorPos(m_window, &m_mouse_xpos, &m_mouse_ypos);

        // Reset mouse position for next frame
        glfwSetCursorPos(m_window, m_width / 2, m_height / 2);

        // Compute new orientation
        m_horizontal_angle += m_mouse_speed * float(m_width / 2 - m_mouse_xpos);
        m_vertical_angle += m_mouse_speed * float(m_height / 2 - m_mouse_ypos);
    }

    if (m_vertical_angle > 2.00f)
        m_vertical_angle = 2.00f;
    if (m_vertical_angle < -2.00f)
        m_vertical_angle = -2.00f;


    // region Main menu
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SUPER) == GLFW_RELEASE
        && glfwGetKey(m_window, GLFW_KEY_P) == GLFW_PRESS) {
        m_main_menu = !m_main_menu;
        if (m_main_menu) {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(m_window, m_width / 2, m_height / 2);
        }
    }
    // endregion


    // Direction : Spherical coordinates to Cartesian coordinates conversion
    m_direction = glm::vec3(
            cos(m_vertical_angle) * sin(m_horizontal_angle),
            sin(m_vertical_angle),
            cos(m_vertical_angle) * cos(m_horizontal_angle)
    );

    // Right vector
    glm::vec3 right(
            sin(m_horizontal_angle - 3.14f / 2.0f),
            0,
            cos(m_horizontal_angle - 3.14f / 2.0f)
    );

    // Up vector
    glm::vec3 up = glm::cross(right, m_direction);

    m_y_dir = up;
    m_x_dir = right;
    m_z_dir = m_direction;

    // Move forward
    if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS
        || glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
        m_position += m_direction * delta_time * m_speed;
    }

    // Move backward
    if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS
        || glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
        m_position -= m_direction * delta_time * m_speed;
    }

    // Move right
    if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS
        || glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
        m_position += right * delta_time * m_speed;
    }

    // Move left
    if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS
        || glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
        m_position -= right * delta_time * m_speed;
    }

    // Move up
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_position += up * delta_time * m_speed;
    }

    // Move bottom
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        m_position -= up * delta_time * m_speed;
    }

    // - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
//    float FoV = m_FOV;


    // Projection matrix : 45deg Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    m_proj_matrix = glm::perspective(
            glm::radians(m_fovy),
            m_width / m_height,
            0.1f,
            200.0f
    );

    // View matrix
    m_view_matrix = glm::lookAt(
            m_position,           // Camera is here
            m_position + m_direction, // and looks here : at the same position, plus "m_direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // For the next frame, the "last time" will be "now"
    last_time = current_time;
}
