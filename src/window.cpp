#include "window.h"
#include <iostream>
#include "configuration.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// region Callbacks

void OnWindowResize(GLFWwindow* window, int width, int height) {
    Camera::GetInstance()->SetWidthHeight(float(width), float(height));
}

void OnKeyEnter(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Camera* camera = Camera::GetInstance();
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_I) {

            if (camera->m_camera_view_type == CameraViewType::NONE) {
                camera->m_camera_view_type = CameraViewType::FRONT;
                camera->m_position = glm::vec3(-8.6f, 7.3f, 14.5f);
                camera->m_vertical_angle = -0.5f;
                camera->m_horizontal_angle = -3.7f;
            } else if (camera->m_camera_view_type == CameraViewType::FRONT) {
                camera->m_camera_view_type = CameraViewType::BACK;
                camera->m_position = glm::vec3(4.8f, 1.85f, -8.75f);
                camera->m_vertical_angle = -0.36f;
                camera->m_horizontal_angle = 5.85f;
            } else if (camera->m_camera_view_type == CameraViewType::BACK) {
                camera->m_camera_view_type = CameraViewType::DYNAMIC;
            } else {
                camera->m_camera_view_type = CameraViewType::NONE;
            }
        }
        else if (key == GLFW_KEY_L) {
            camera->flashlight->m_on = !camera->flashlight->m_on;
        }
        else if (key == GLFW_KEY_R) {
            Configuration();
        }
        else if (key == GLFW_KEY_N) {
            skybox->ChangeSkybox();
        }
        else if (key == GLFW_KEY_J) {
            sun_shines = !sun_shines;
            phong_shader->Bind();
            phong_shader->SetInt1("sun_shines", sun_shines);
        }
        else if (key == GLFW_KEY_F) {
            camera->fog = !camera->fog;
            phong_shader->Bind();
            phong_shader->SetInt1("fog", camera->fog);
            water_shader->Bind();
            water_shader->SetInt1("fog", camera->fog);
            skybox->shader->Bind();
            skybox->shader->SetInt1("fog", camera->fog);
        }
    }
}

void OnMouseClick(GLFWwindow* window, int button, int action, int mods) {
    Camera* camera = Camera::GetInstance();
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (camera->distance_to_picking_object < 4.0f) {
            if (camera->looking_at_object == 1) {
//            std::cout << camera->distance_to_picking_object << std::endl;
                island_moving = !island_moving;
            } else if (camera->looking_at_object == 2) {
                clouds_moving = !clouds_moving;
            } else if (camera->looking_at_object == 3) {
                flame_burns = !flame_burns;
                phong_shader->Bind();
                if (!flame_burns) {
                    phong_shader->SetVec3("point_lights[1].position", glm::vec3(0));
                    phong_shader->SetVec3("point_lights[1].ambient", glm::vec3(0));
                    phong_shader->SetVec3("point_lights[1].diffuse", glm::vec3(0));
                } else {
                    phong_shader->SetVec3("point_lights[1].position", campfire->m_position);
                    phong_shader->SetVec3("point_lights[1].ambient", campfire->m_ambient);
                    phong_shader->SetVec3("point_lights[1].diffuse", campfire->m_diffuse);
                }
            }
        }
    }
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//        std::cout << "right pressed" << std::endl;
}

// endregion

GLFWwindow* InitWindow(int width, int height) {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(
            width,
            height,
            "Floating islands",
            NULL,
            NULL
    );

    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create glfw window" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(60);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Failed to initialize glew" << std::endl;
        return nullptr;
    }

    std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW   : " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "GLFW   : " << glfwGetVersionString() << std::endl << std::endl;

    glfwSetKeyCallback(window, OnKeyEnter);
    glfwSetMouseButtonCallback(window, OnMouseClick);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set callback on aspect change
    glfwSetFramebufferSizeCallback(window, OnWindowResize);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    // region ImGui setup
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
    // endregion

    // Background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    return window;
}