#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "light.h"

enum CameraViewType {
    NONE, BACK, FRONT, DYNAMIC
};

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

    [[nodiscard]] const glm::mat4& GetMatProj() const { return m_proj_matrix; }

    [[nodiscard]] const glm::mat4& GetMatView() const { return m_view_matrix; }

    [[nodiscard]] const glm::vec3& GetPosition() const { return m_position; }

    [[nodiscard]] const glm::mat4& GetDirections() {
        m_directions[0][0] = m_x_dir[0];
        m_directions[1][0] = m_x_dir[1];
        m_directions[2][0] = m_x_dir[2];

        m_directions[0][1] = m_y_dir[0];
        m_directions[1][1] = m_y_dir[1];
        m_directions[2][1] = m_y_dir[2];

        m_directions[0][2] = m_z_dir[0];
        m_directions[1][2] = m_z_dir[1];
        m_directions[2][2] = m_z_dir[2];
        return m_directions;
    }

    void SetWidthHeight(float width, float height);

//private:
    GLFWwindow* m_window;

    float m_width = 0;
    float m_height = 0;

    bool m_main_menu = false;
    bool m_static_view = false;
    CameraViewType m_camera_view_type = CameraViewType::NONE;

    float m_horizontal_angle = 3.14f;
    float m_vertical_angle = 0.0f;
    glm::vec3 m_position = glm::vec3(0, 0, 10);

    float m_speed = 6.0f; // units per seconds
    float m_mouse_speed = 0.005f;

    double m_mouse_xpos = 0;
    double m_mouse_ypos = 0;

    float m_fovy = 45.0f; // Field of View

    glm::mat4 m_proj_matrix = glm::mat4(1.0f);
    glm::mat4 m_view_matrix = glm::mat4(1.0f);
//    glm::mat4 m_view_proj_matrix = glm::mat4(1.0f);

    glm::vec3 m_x_dir = glm::vec3(0.0f);
    glm::vec3 m_y_dir = glm::vec3(0.0f);
    glm::vec3 m_z_dir = glm::vec3(0.0f);

    glm::mat4 m_directions = glm::mat4(1.0f); // Axis direction
    glm::vec3 m_direction = glm::vec3(0.0f); // Camera direction

    SpotLight* flashlight;
    bool fog = false;
    unsigned int looking_at_object = 0;
    float distance_to_picking_object = 0.0f;


};
