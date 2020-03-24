#include <iostream>

#include "camera.h"
#include "window.h"


// Allocate pointer for camera
Camera *Camera::s_instance = nullptr;

int main() {

    GLFWwindow* window = InitWindow();
    if (window == nullptr) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    Camera* camera = Camera::GetInstance(window);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.1f, 0.4f, 0.8f, 1.0f);

        camera->UpdateViewProjection();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && !glfwWindowShouldClose(window));


    return 0;
}
