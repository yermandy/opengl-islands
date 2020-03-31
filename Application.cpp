#include <iostream>

#include "camera.h"
#include "window.h"
#include "shader.h"
#include "renderer.h"
#include "shapes/shapes.h"

// Allocate pointer for camera
Camera *Camera::s_instance = nullptr;

int main() {

    int width = 640;
    int height = 480;

    GLFWwindow* window = InitWindow(width, height);
    if (window == nullptr) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    Camera* camera = Camera::GetInstance(window);

    Cube cube;

    Axes axes;

    Shader shader("res/shaders/black_white.glsl");
    shader.Bind();

    Shader shader_3d("res/shaders/3d_shader.glsl");
    shader_3d.Bind();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background

    glm::mat4 translate;

    Renderer renderer;

    do {
        renderer.Clear();

        camera->UpdateViewProjection();
        glm::mat4 VP = camera->GetViewProjectionMatrix();

//        {
//            translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
//            shader_3d.SetUniformMat4f("u_MPV", VP * translate);
//            renderer.DrawTriangles(*cube.vao, *cube.ibo, shader_3d);
//        }
//
        {
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -1.5f, 3.0f));
            shader_3d.SetUniformMat4f("u_MPV", VP * translate);
            renderer.DrawTriangles(*cube.vao, *cube.ibo, shader_3d);
        }

        {
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 20.0f));
            shader_3d.SetUniformMat4f("u_MPV", VP * translate);
            renderer.DrawTriangles(*cube.vao, *cube.ibo, shader_3d);
        }

        // region World axes
        {
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(10, 10, 160, 160);
            shader_3d.SetUniformMat4f("u_MPV", camera->GetDirections());
            renderer.DrawLines(*axes.vao, *axes.ibo, shader_3d);
            glViewport(0, 0, width, height);
        }
        // endregion

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && !glfwWindowShouldClose(window));


    return 0;
}