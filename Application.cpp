#include <iostream>

#include "camera.h"
#include "window.h"
#include "shader.h"
#include "buffers/buffers.h"

// Allocate pointer for camera
Camera *Camera::s_instance = nullptr;

int main() {

    GLFWwindow* window = InitWindow();
    if (window == nullptr) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    Camera* camera = Camera::GetInstance(window);

    float triangle_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f
    };

//    float triangle_indices[] = {
//        0, 1, 2
//    };

    VertexBuffer triangle_vbo(triangle_data,  sizeof(triangle_data));

    BufferLayout triangle_layout;
    triangle_layout.Push(GL_FLOAT, 3, GL_FALSE);

    VertexArray triangle_vao;
    triangle_vao.AddBuffer(triangle_vbo, triangle_layout);

//    IndexBuffer triangle_ibo(triangle_indices, 6);
    Shader shader("res/shaders/black_white.glsl");
    shader.Bind();

    glClearColor(0.1f, 0.4f, 0.8f, 1.0f); // Background

    glm::mat4 translate;

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        std::cout << camera->GetViewProjectionMatrix() << std::endl;
        camera->UpdateViewProjection();
        glm::mat4 VP = camera->GetViewProjectionMatrix();
//        glm::mat4 MVP = VP;

        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
//        shader.SetUniformMat4f("u_view_proj", VP);
//        shader.SetUniformMat4f("u_transform", translate);
        shader.SetUniformMat4f("u_MPV", VP * translate);


        glDrawArrays(GL_TRIANGLES, 0, 3);
//        LOG(glDrawElements(GL_TRIANGLES, triangle_ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

        translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
//        shader.SetUniformMat4f("u_view_proj", VP);
//        shader.SetUniformMat4f("u_transform", translate);
        shader.SetUniformMat4f("u_MPV", VP * translate);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && !glfwWindowShouldClose(window));


    return 0;
}