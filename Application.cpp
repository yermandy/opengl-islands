#include <iostream>

#include "camera.h"
#include "window.h"
#include "shader.h"
#include "renderer.h"

// Allocate pointer for camera
Camera *Camera::s_instance = nullptr;

int main() {

    GLFWwindow* window = InitWindow();
    if (window == nullptr) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    Camera* camera = Camera::GetInstance(window);


    // region triangle

    float triangle_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f
    };

    unsigned int triangle_indices[] = {
            0, 1, 2
    };

    VertexBuffer triangle_vbo(triangle_data,  sizeof(triangle_data));

    BufferLayout triangle_layout;
    triangle_layout.Push(GL_FLOAT, 3, GL_FALSE);

    VertexArray triangle_vao;
    triangle_vao.AddBuffer(triangle_vbo, triangle_layout);

    IndexBuffer triangle_ibo(triangle_indices, sizeof(triangle_indices));

    // endregion

    // region cube

    float cube_data[6 * 8] = {
//            x      y      z       r     g     b
            -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f, // 0
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f, // 1
            -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f, // 2
            -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f, // 3
             1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f, // 4
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 1.0f, // 5
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f, // 6
             1.0f,  1.0f,  1.0f,   1.0f, 1.0f, 1.0f, // 7
    };

    unsigned int cube_indices[6 * 6] = {
            0, 2, 4,   4, 2, 6, // back face
            0, 1, 2,   2, 1, 3, // left face
            1, 5, 3,   3, 5, 7, // front face
            5, 4, 7,   7, 4, 6, // right face
            3, 7, 2,   2, 7, 6, // upper face
            0, 4, 1,   1, 4, 5, // lower face
    };

    VertexBuffer cube_vbo(cube_data,  sizeof(cube_data));

    BufferLayout cube_layout;
    cube_layout.Push(GL_FLOAT, 3, GL_FALSE);
    cube_layout.Push(GL_FLOAT, 3, GL_FALSE);

    VertexArray cube_vao;
    cube_vao.AddBuffer(cube_vbo, cube_layout);

    IndexBuffer cube_ibo(cube_indices, sizeof(cube_indices));

    // endregion

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
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            shader.SetUniformMat4f("u_MPV", VP * translate);
            renderer.Draw(triangle_vao, triangle_ibo, shader);
        }

        {
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
            shader.SetUniformMat4f("u_MPV", VP * translate);
            renderer.Draw(triangle_vao, triangle_ibo, shader);
        }

        {
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -1.5f, 3.0f));
            cube_shader.SetUniformMat4f("u_MPV", VP * translate);
            renderer.Draw(cube_vao, cube_ibo, cube_shader);
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && !glfwWindowShouldClose(window));


    return 0;
}