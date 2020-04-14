#include <iostream>

#include "camera.h"
#include "window.h"
#include "shader.h"
#include "renderer.h"
#include "shapes/shapes.h"
#include "mesh.h"

// Allocate pointer for camera
Camera *Camera::s_instance = nullptr;

int main() {

    int width = 1024;
    int height = 720;

    GLFWwindow* window = InitWindow(width, height);
    if (window == nullptr) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    Camera* camera = Camera::GetInstance(window);

    Cube cube;
    Axes axes;

    Shader phong_shader("res/shaders/phong.shader");
    Shader standard_shader("res/shaders/standard.shader");

    // Background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glm::mat4 translate;
    glm::mat4 M;

    Mesh sphere("res/objects/sphere.obj", phong_shader);

    Renderer renderer;

    do {
        renderer.Clear();

        camera->UpdateViewProjection();
        glm::mat4 VP = camera->GetViewProjectionMatrix();
        glm::mat4 V = camera->GetViewMatrix();

//        for (float i = -10; i < 11.0; i += 2.001) {
//            for (float  j = -10; j < 11.0;  j += 2.001) {
//                translate = glm::translate(glm::mat4(1.0f), glm::vec3(i, j, .0f));
//                standard_shader.Bind();
//                standard_shader.SetUniformMat4f("u_MPV", VP * translate);
//                renderer.DrawTriangles(*cube.vao, *cube.ibo, standard_shader);
//            }
//        }

        {
            M = glm::mat4(1.0f);
            M = glm::translate(M, glm::vec3(0.0f, 0.0f, -3.0f));
            phong_shader.Bind();
            phong_shader.SetUniformMat4f("u_MPV", VP * M);
            phong_shader.SetUniformMat4f("u_M", M);
            phong_shader.SetUniformMat4f("u_V", V);
            phong_shader.SetUniform3fv("u_light_position", glm::vec3(0.0f, 10.0f, 0.0f));
            renderer.DrawTriangles(*sphere.vao, *sphere.ibo, phong_shader);
        }

//        {
//            translate = glm::translate(glm::mat4(1.0f), glm::vec3(.0f, .0f, .0f));
//            phong_shader.Bind();
//            phong_shader.SetUniformMat4f("u_MPV", VP * translate);
//            renderer.DrawTriangles(*cube.vao, *cube.ibo, phong_shader);
//        }
//
//        {
//            translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 20.0f));
//            standard_shader.SetUniformMat4f("u_MPV", VP * translate);
//            renderer.DrawTriangles(*cube.vao, *cube.ibo, standard_shader);
//        }

        // region World axes
        {
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(10, 10, 160, 160);
            standard_shader.Bind();
            standard_shader.SetUniformMat4f("u_MPV", camera->GetDirections());
            renderer.DrawLines(*axes.vao, *axes.ibo, standard_shader);
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