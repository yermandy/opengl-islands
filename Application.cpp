#include <iostream>

#include "camera.h"
#include "window.h"
#include "shader.h"
#include "renderer.h"
#include "shapes/shapes.h"

// Allocate pointer for camera
Camera *Camera::s_instance = nullptr;

int main() {

    GLFWwindow* window = InitWindow();
    if (window == nullptr) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    Camera* camera = Camera::GetInstance(window);

    Cube cube;

    Shader shader("res/shaders/black_white.glsl");
    shader.Bind();

    Shader cube_shader("res/shaders/3d_shader.glsl");
    cube_shader.Bind();

    glClearColor(0.1f, 0.4f, 0.8f, 1.0f); // Background

    glm::mat4 translate;

    Renderer renderer;

    do {
        renderer.Clear();

        camera->UpdateViewProjection();
        glm::mat4 VP = camera->GetViewProjectionMatrix();

        {
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
            cube_shader.SetUniformMat4f("u_MPV", VP * translate);
            renderer.Draw(*cube.vao, *cube.ibo, cube_shader);
        }

        {
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -1.5f, 3.0f));
            cube_shader.SetUniformMat4f("u_MPV", VP * translate);
            renderer.Draw(*cube.vao, *cube.ibo, cube_shader);
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && !glfwWindowShouldClose(window));


    return 0;
}