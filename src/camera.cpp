#include "camera.h"

#include <iostream>


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
    double currentTime = glfwGetTime();
    auto delta_time = float(currentTime - last_time);

    if (!m_main_menu) {
        // Get mouse position
        glfwGetCursorPos(m_window, &m_mouse_xpos, &m_mouse_ypos);

        // Reset mouse position for next frame
        glfwSetCursorPos(m_window, m_width / 2, m_height / 2);

        // Compute new orientation
        m_horizontal_angle += m_mouse_speed * float(m_width / 2 - m_mouse_xpos);
        m_vertical_angle += m_mouse_speed * float(m_height / 2 - m_mouse_ypos);
    }


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


    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            cos(m_vertical_angle) * sin(m_horizontal_angle),
            sin(m_vertical_angle),
            cos(m_vertical_angle) * cos(m_horizontal_angle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            sin(m_horizontal_angle - 3.14f / 2.0f),
            0,
            cos(m_horizontal_angle - 3.14f / 2.0f)
    );

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    // Move forward
    if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS
        || glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
        m_position += direction * delta_time * m_speed;
    }

    // Move backward
    if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS
        || glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
        m_position -= direction * delta_time * m_speed;
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
            100.0f
    );

    // View matrix
    m_view_matrix = glm::lookAt(
            m_position,           // Camera is here
            m_position + direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    m_view_proj_matrix = m_proj_matrix * m_view_matrix;

    // For the next frame, the "last time" will be "now"
    last_time = currentTime;
}
