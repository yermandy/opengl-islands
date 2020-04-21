#include <iostream>

#include "camera.h"
#include "window.h"
#include "shader.h"
#include "renderer.h"
#include "shapes/shapes.h"
#include "mesh.h"
#include "light.h"
#include "texture.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Allocate pointer for camera
Camera* Camera::s_instance = nullptr;

int main() {

    int width = 1024;
    int height = 720;

    GLFWwindow* window = InitWindow(width, height);
    if (window == nullptr) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    Camera* camera = Camera::GetInstance(window);

    Axes axes;

    Mesh cube("res/objects/cube.obj");

    Shader phong_shader("res/shaders/phong.shader");
    phong_shader.Bind();
    phong_shader.SetVec3("u_light.ambient", glm::vec3(0.1f));
    phong_shader.SetVec3("u_light.diffuse", glm::vec3(0.7f));
    phong_shader.SetVec3("u_light.specular", glm::vec3(1.0f));

    Shader standard_shader("res/shaders/standard.shader");

    // Background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glm::vec3 translate;
    glm::mat4 M;

    Mesh sun_object("res/objects/sun.obj");


    // region Island
    std::vector<Mesh> island;

    glm::vec3 island_position = glm::vec3(0.0f, -8.0f, 0.0f);
    Mesh island_ground_1("res/objects/island/island_ground_1.obj", island_position);
    Mesh island_ground_2("res/objects/island/island_ground_2.obj", island_position);
    Mesh island_mountains("res/objects/island/island_mountains.obj", island_position);
    Mesh island_grass("res/objects/island/island_grass.obj", island_position);
    Mesh island_water("res/objects/island/island_water.obj", island_position);
    Mesh island_cloud_1("res/objects/island/island_cloud_1.obj", island_position);
    Mesh island_cloud_2("res/objects/island/island_cloud_2.obj", island_position);
    Mesh island_cloud_3("res/objects/island/island_cloud_3.obj", island_position);
    Mesh island_cloud_4("res/objects/island/island_cloud_4.obj", island_position);

    island.push_back(island_ground_1);
    island.push_back(island_ground_2);
    island.push_back(island_mountains);
    island.push_back(island_grass);
    island.push_back(island_water);
    island.push_back(island_cloud_1);
    island.push_back(island_cloud_2);
    island.push_back(island_cloud_3);
    island.push_back(island_cloud_4);

    // endregion

    // region ImGui setup
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
    // endregion

    DirectionalLight sun(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.0f));
    PointLight lamp(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.0f, -3.0f, 1.5f));
    Mesh lamp_mesh("res/objects/cube.obj", lamp.m_position);
    Mesh test_mesh("res/objects/sphere.obj");
//    Cube lamp_mesh;

    phong_shader.Bind();
    phong_shader.SetVec3("point_lights[0].position", lamp.m_position);
    phong_shader.SetVec3("point_lights[0].ambient", lamp.m_ambient);
    phong_shader.SetVec3("point_lights[0].diffuse", lamp.m_diffuse);
    phong_shader.SetVec3("point_lights[0].specular", lamp.m_specular);
    phong_shader.SetFloat1("point_lights[0].constant", lamp.m_constant);
    phong_shader.SetFloat1("point_lights[0].linear", .2f);

    Renderer renderer;

    Texture texture("res/textures/cloud_texture.jpg");
//    Texture sun_texture("res/textures/sun_texture.jpg");
//    LOG(glEnable(GL_BLEND));
//    LOG(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//    LOG(glBlendFunc(GL_ONE, GL_ONE));


    do {
        renderer.Clear();

        camera->UpdateViewProjection();
        glm::mat4 P = camera->GetMatProj();
        glm::mat4 V = camera->GetMatView();
        glm::mat4 VP = P * V;
        phong_shader.Bind();


        double time = glfwGetTime();

//        for (float i = -10; i < 11.0; i += 2.001) {
//            for (float  j = -10; j < 11.0;  j += 2.001) {
//                translate = glm::translate(glm::mat4(1.0f), glm::vec3(i, j, .0f));
//                standard_shader.Bind();
//                standard_shader.SetMat4("u_MVP", VP * translate);
//                renderer.DrawTriangles(*cube.vao, *cube.ibo, standard_shader);
//            }
//        }

//        {
//            M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
//            phong_shader.Bind();
//            texture.Bind();
//            phong_shader.SetMVP(VP * M, M, V);
//            phong_shader.SetMeshMaterial(test_mesh);
//            phong_shader.SetInt1("u_tex_sampler", 0);
//            phong_shader.SetInt1("u_material.use_texture", 1);
//            renderer.DrawTriangles(*test_mesh.vao, *test_mesh.ibo, phong_shader);
//            phong_shader.SetInt1("u_material.use_texture", 0);
//        }

        {
            M = glm::translate(glm::mat4(1.0f), lamp.m_position);
            M = glm::scale(M, glm::vec3(0.1f));
            standard_shader.Bind();
            standard_shader.SetInt1("u_use_texture", 0);
            standard_shader.SetMat4("u_MVP", VP * M);
            renderer.DrawTriangles(*lamp_mesh.vao, *lamp_mesh.ibo, standard_shader);
        }

        {
            for (const Mesh& island_part : island) {
                M = glm::mat4(1.0f);
                M = glm::translate(M, island_part.m_position);
                M = glm::scale(M, island_part.m_scale);
                phong_shader.Bind();
                phong_shader.SetInt1("u_material.use_texture", 0);
                phong_shader.SetMVP(VP * M, M, V);
                phong_shader.SetMeshMaterial(island_part);
                renderer.DrawTriangles(*island_part.vao, *island_part.ibo, phong_shader);
            }
        }


        // region Sun
        {
            sun.m_direction[0] = 10000 * glm::sin(-1000 + time * .1);
            sun.m_direction[1] = 10000 * glm::cos(-1000 + time * .1);

            sun.m_direction = glm::vec4(sun.m_direction, 1);
            translate = glm::vec3(sun.m_direction[0] / 100, sun.m_direction[1] / 100, sun.m_direction[2]);
            M = glm::translate(glm::mat4(1.0f), translate);
            M = glm::scale(M, glm::vec3(2.0f));
            M = glm::rotate(M, glm::radians(float(time) * 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            standard_shader.Bind();
            sun_object.m_texture->Bind();
            standard_shader.SetInt1("u_tex_sampler", 0);
            standard_shader.SetInt1("u_use_texture", 1);
            standard_shader.SetMat4("u_MVP", VP * M);
            renderer.DrawTriangles(*sun_object.vao, *sun_object.ibo, standard_shader);
        }
        // endregion


//        {
//            M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
//            M = glm::scale(M, glm::vec3(0.5f));
//            phong_shader.Bind();
//            phong_shader.SetMVP(VP * M, M, V);
//            renderer.DrawTriangles(*cube.vao, *cube.ibo, phong_shader);
//        }

        // region World axes
        {
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(10, 10, 160, 160);
            standard_shader.Bind();
            standard_shader.SetInt1("u_use_texture", 0);
            standard_shader.SetMat4("u_MVP", camera->GetDirections());
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

            ImGui::SliderFloat3("light position", &lamp.m_position.x, -25.0f, 25.0f);

            ImGui::Separator();

            phong_shader.Bind();
            phong_shader.SetVec3("point_lights[0].position", lamp.m_position);
            phong_shader.SetVec3("sun.direction", V * glm::vec4(sun.m_direction, 1.0f));

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