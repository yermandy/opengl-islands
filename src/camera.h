#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:
    static Camera* s_instance;

    Camera(GLFWwindow* window);


    static Camera* GetInstance(GLFWwindow* window = nullptr) {
        if (!s_instance)
            s_instance = new Camera(window);
        return s_instance;
    }

    virtual ~Camera();

    void UpdateViewProjection();

    [[nodiscard]] const glm::mat4& GetProjectionMatrix() const { return m_proj_matrix; }

    [[nodiscard]] const glm::mat4& GetViewMatrix() const { return m_view_matrix; }

    [[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const { return m_view_proj_matrix; }

    void SetWidthHeight(float width, float height);

private:
    GLFWwindow* m_window;

    float m_width = 0;
    float m_height = 0;
    bool m_main_menu = false;

    float m_horizontal_angle = 3.14f;
    float m_vertical_angle = 0.0f;
    glm::vec3 m_position = glm::vec3(0, 0, 10);

    float m_speed = 6.0f; // units per seconds
    float m_mouse_speed = 0.005f;

    double m_mouse_xpos = 0;
    double m_mouse_ypos = 0;

    float m_fovy = 45.0f; // Field of View

    glm::mat4 m_proj_matrix;
    glm::mat4 m_view_matrix;
    glm::mat4 m_view_proj_matrix;

private:
    void OnWindowResize(GLFWwindow* window, int width, int height);
};
