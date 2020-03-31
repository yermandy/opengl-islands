#include "window.h"
#include <iostream>

// region Callbacks

void OnWindowResize(GLFWwindow* window, int width, int height) {
    Camera::GetInstance()->SetWidthHeight(float(width), float(height));
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
            "OpenGL Universe",
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
    std::cout << "GLFW   : " << glfwGetVersionString() << std::endl;

//    glfwSetKeyCallback(window, onKeyEnter);
//    glfwSetScrollCallback(window, onScroll);

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

    return window;
}