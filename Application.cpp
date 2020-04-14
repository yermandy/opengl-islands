#include <iostream>

#include "camera.h"
#include "window.h"
#include "shader.h"
#include "renderer.h"
#include "shapes/shapes.h"
#include "mesh.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
    phong_shader.Bind();
    phong_shader.SetVec3("u_light.ambient", glm::vec3(0.1f));
    phong_shader.SetVec3("u_light.diffuse", glm::vec3(0.7f));
    phong_shader.SetVec3("u_light.specular", glm::vec3(1.0f));

    Shader standard_shader("res/shaders/standard.shader");

    // Background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glm::mat4 translate;
    glm::mat4 M;

    Mesh sphere("res/objects/sphere.obj", phong_shader);

    Renderer renderer;

    // region ImGui setup
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
    // endregion

    glm::vec3 light_ambient(0.1f);
    glm::vec3 light_diffuse(0.7f);
    glm::vec3 light_specular(1.0f);

    do {
        renderer.Clear();

        camera->UpdateViewProjection();
        glm::mat4 VP = camera->GetViewProjectionMatrix();
        glm::mat4 V = camera->GetViewMatrix();

//        for (float i = -10; i < 11.0; i += 2.001) {
//            for (float  j = -10; j < 11.0;  j += 2.001) {
//                translate = glm::translate(glm::mat4(1.0f), glm::vec3(i, j, .0f));
//                standard_shader.Bind();
//                standard_shader.SetMat4("u_MPV", VP * translate);
//                renderer.DrawTriangles(*cube.vao, *cube.ibo, standard_shader);
//            }
//        }

        {
            M = glm::mat4(1.0f);
            M = glm::translate(M, glm::vec3(0.0f, 0.0f, -3.0f));
            phong_shader.Bind();
            phong_shader.SetMat4("u_MPV", VP * M);
            phong_shader.SetMat4("u_M", M);
            phong_shader.SetMat4("u_V", V);
            phong_shader.SetVec3("u_material.ambient", sphere.m_ambient);
            phong_shader.SetVec3("u_material.diffuse", sphere.m_diffuse);
            phong_shader.SetVec3("u_material.specular", sphere.m_specular);
            phong_shader.SetFloat1("u_material.shininess", sphere.m_shininess);
            phong_shader.SetVec3("u_light_position", glm::vec3(0.0f, 10.0f, 0.0f));
            renderer.DrawTriangles(*sphere.vao, *sphere.ibo, phong_shader);
        }

//        {
//            translate = glm::translate(glm::mat4(1.0f), glm::vec3(.0f, .0f, .0f));
//            phong_shader.Bind();
//            phong_shader.SetMat4("u_MPV", VP * translate);
//            renderer.DrawTriangles(*cube.vao, *cube.ibo, phong_shader);
//        }
//
//        {
//            translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 20.0f));
//            standard_shader.SetMat4("u_MPV", VP * translate);
//            renderer.DrawTriangles(*cube.vao, *cube.ibo, standard_shader);
//        }

        // region World axes
        {
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(10, 10, 160, 160);
            standard_shader.Bind();
            standard_shader.SetMat4("u_MPV", camera->GetDirections());
            renderer.DrawLines(*axes.vao, *axes.ibo, standard_shader);
            glViewport(0, 0, width, height);
        }
        // endregion

        // region ImGui window
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {

            ImGui::Begin("Debug");

            ImGui::SliderFloat3("ambient", &sphere.m_ambient.x, 0.0f, 1.0f);
            ImGui::SliderFloat3("diffuse", &sphere.m_diffuse.x, 0.0f, 1.0f);
            ImGui::SliderFloat3("specular", &sphere.m_specular.x, 0.0f, 1.0f);
            ImGui::SliderFloat("shininess", &sphere.m_shininess, 0.0f, 100.0f);

            ImGui::Separator();

            ImGui::SliderFloat3("light ambient", &light_ambient.x, 0.0f, 1.0f);
            ImGui::SliderFloat3("light diffuse", &light_diffuse.x, 0.0f, 1.0f);
            ImGui::SliderFloat3("light specular", &light_specular.x, 0.0f, 1.0f);



            phong_shader.Bind();
            phong_shader.SetVec3("u_light.ambient", light_ambient);
            phong_shader.SetVec3("u_light.diffuse", light_diffuse);
            phong_shader.SetVec3("u_light.specular", light_specular);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // endregion

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && !glfwWindowShouldClose(window));


    return 0;
}