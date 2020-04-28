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
#include <glm/gtx/spline.hpp>
#include <glm/gtx/string_cast.hpp>

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

    Shader water_shader("res/shaders/water.shader");

    // Background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glm::vec3 translate;
    glm::mat4 M;

    Mesh sun_object("res/objects/sun.obj");


    // region Island
    std::vector<Mesh*> island;

    glm::vec3 island_position = glm::vec3(0.0f, -8.0f, 0.0f);
//    glm::vec3 island_position = glm::vec3(0.0f, 0.0f, 0.0f);
    Mesh island_ground_1("res/objects/island/island_ground_1.obj", island_position);
    Mesh island_ground_2("res/objects/island/island_ground_2.obj", island_position);
    Mesh island_mountains("res/objects/island/island_mountains.obj", island_position);
    Mesh island_grass("res/objects/island/island_grass.obj", island_position);
    Mesh island_water("res/objects/island/island_water.obj", island_position);
    Mesh island_cloud_1("res/objects/island/island_cloud_1.obj", island_position);
    Mesh island_cloud_2("res/objects/island/island_cloud_2.obj", island_position);
    Mesh island_cloud_3("res/objects/island/island_cloud_3.obj", island_position);
    Mesh island_cloud_4("res/objects/island/island_cloud_4.obj", island_position);
    Mesh island_small_floating_stone("res/objects/island/island_small_floating_stone.obj", island_position);
    Mesh island_red_gates("res/objects/island/island_red_gates.obj", island_position);
    Mesh island_black_gates("res/objects/island/island_black_gates.obj", island_position);
    Mesh island_stone_lamps("res/objects/island/island_stone_lamps.obj", island_position);
    Mesh island_bridge("res/objects/island/island_bridge.obj", island_position, glm::vec3(1.1f, 1.0f, 1.1f));
    Mesh island_trees_wood("res/objects/island/island_trees_wood.obj", island_position);
    Mesh island_leaves_1("res/objects/island/island_leaves_1.obj", island_position);
    Mesh island_leaves_2("res/objects/island/island_leaves_2.obj", island_position);
    Mesh island_leaves_3("res/objects/island/island_leaves_3.obj", island_position);

    island.push_back(&island_ground_1);
    island.push_back(&island_ground_2);
    island.push_back(&island_mountains);
    island.push_back(&island_grass);
//    island.push_back(&island_water);
    island.push_back(&island_cloud_1);
    island.push_back(&island_cloud_2);
    island.push_back(&island_cloud_3);
    island.push_back(&island_cloud_4);
    island.push_back(&island_red_gates);
    island.push_back(&island_black_gates);
    island.push_back(&island_stone_lamps);
    island.push_back(&island_bridge);
    island.push_back(&island_trees_wood);
    island.push_back(&island_leaves_1);
    island.push_back(&island_leaves_2);
    island.push_back(&island_leaves_3);

    // endregion

    // region ImGui setup
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
    // endregion

    DirectionalLight sun(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.0f));
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
    Texture sun_texture("res/textures/sun_texture.jpg");
//    LOG(glEnable(GL_BLEND));
//    LOG(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//    LOG(glBlendFunc(GL_ONE, GL_ONE));


    Skybox skybox;

    float refraction;

    float t = 0.0f;

    std::vector<glm::vec3> control_points;

    control_points.emplace_back(0.0f, 0.0f, 0.0f);
    control_points.emplace_back(-5.0f, 0.0f, 4.0f);

    control_points.emplace_back(3.0f, 0.0f, 5.0f);
    control_points.emplace_back(7.0f, 0.0f, 6.0f);

    control_points.emplace_back(4.0f, 0.0f, 8.0f);
    control_points.emplace_back(0.0f, 0.0f, 6.0f);

    control_points.emplace_back(3.0f, 0.0f, 5.0f);
    control_points.emplace_back(5.0f, 0.0f, 2.0f);

    control_points.emplace_back(0.0f, 0.0f, 0.0f);
    control_points.emplace_back(-5.0f, 0.0f, 4.0f);

    do {
        renderer.Clear();

        camera->UpdateViewProjection();
        glm::mat4 P = camera->GetMatProj();
        glm::mat4 V = camera->GetMatView();
        glm::mat4 VP = P * V;


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
            for (const Mesh* island_part : island) {
                M = glm::mat4(1.0f);
                M = glm::translate(M, island_part->m_position);
                M = glm::scale(M, island_part->m_scale);
                phong_shader.Bind();
                phong_shader.SetInt1("u_material.use_texture", 0);
                phong_shader.SetMVP(VP * M, M, V);
                phong_shader.SetMeshMaterial(*island_part);
                renderer.DrawTriangles(*island_part->vao, *island_part->ibo, phong_shader);
            }
        }


        // region Sun
        {
            sun.m_direction[0] = 5000 * glm::sin(time * .5);
            sun.m_direction[1] = 10000;
            sun.m_direction[2] = 5000 * glm::cos(time * .5);


            sun.m_direction = glm::vec4(sun.m_direction, 1);
            translate = glm::vec3(sun.m_direction[0] / 100, sun.m_direction[1] / 100, sun.m_direction[2] / 100);
            M = glm::translate(glm::mat4(1.0f), translate);
            M = glm::scale(M, glm::vec3(2.0f));
            M = glm::rotate(M, glm::radians(float(time) * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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


        // region Skybox
        {
            skybox.shader->Bind();
            skybox.shader->SetInt1("u_skybox", 0);
            glm::mat4 inverse_PV = glm::inverse(P * glm::mat4(glm::mat3(V)));
            skybox.shader->SetMat4("u_inv_PV", inverse_PV);
            skybox.Draw();
        }
        // endregion

        // region Small island
        {
            t = float(time / 3.0f);
            int t_i = (int(t) % 4) * 2;
            glm::vec3 point = glm::hermite(control_points[0 + t_i], control_points[1 + t_i],
                                           control_points[2 + t_i], control_points[3 + t_i],
                                           glm::mod(t, 1.0f));


            island_small_floating_stone.m_position[0] = point[0];
            island_small_floating_stone.m_position[2] = point[2];

            M = glm::mat4(1.0f);
            M = glm::translate(M, island_small_floating_stone.m_position);
            M = glm::scale(M, island_small_floating_stone.m_scale);

            // Rotate small island
            M = glm::translate(M, island_small_floating_stone.m_pivot);
            M = glm::rotate(M, glm::radians(float(time) * 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            M = glm::translate(M, -island_small_floating_stone.m_pivot);

            phong_shader.Bind();
            phong_shader.SetInt1("u_material.use_texture", 0);
            phong_shader.SetMVP(VP * M, M, V);
            phong_shader.SetMeshMaterial(island_small_floating_stone);
            renderer.DrawTriangles(*island_small_floating_stone.vao, *island_small_floating_stone.ibo, phong_shader);
        }

        // endregion

//        {
//            M = glm::translate(glm::mat4(1.0f), point);
//            M = glm::scale(M, glm::vec3(0.5f));
//            phong_shader.Bind();
//            phong_shader.SetMVP(VP * M, M, V);
//            renderer.DrawTriangles(*island_small_floating_stone.vao, *island_small_floating_stone.ibo, phong_shader);
//        }

        {
            LOG(glEnable(GL_BLEND));
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            water_shader.Bind();
            skybox.BindTexture();
            water_shader.SetVec3("u_camera_position", camera->GetPosition());
            M = glm::mat4(1.0f);
//            M = glm::translate(M, glm::vec3(0.0f, 0.0f, 3.0f));
//            M = glm::rotate(M, glm::radians(float(time) * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//            M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
            water_shader.SetMat4("u_M", M);
            water_shader.SetMat4("u_VP", VP);
            water_shader.SetInt1("u_skybox", 0);
            renderer.DrawTriangles(*cube.vao, *cube.ibo, water_shader);
            LOG(glDisable(GL_BLEND));
        }

        {
            LOG(glEnable(GL_BLEND));
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            water_shader.Bind();
            skybox.BindTexture();
            M = glm::mat4(1.0f);
            M = glm::translate(M, island_water.m_position);
            M = glm::scale(M, island_water.m_scale);
            water_shader.SetVec3("u_camera_position", camera->GetPosition());
            water_shader.SetMat4("u_M", M);
            water_shader.SetMat4("u_VP", VP);
            water_shader.SetInt1("u_skybox", 0);
            water_shader.SetFloat1("u_time", std::cos(std::cos(float(time)) / 6));
            renderer.DrawTriangles(*island_water.vao, *island_water.ibo, water_shader);
            LOG(glDisable(GL_BLEND));
        }


        // region ImGui window
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {

            ImGui::Begin("Debug");

            ImGui::SliderFloat3("light position", &lamp.m_position.x, -25.0f, 25.0f);

            ImGui::Separator();

//            ImGui::ColorPicker3("island diffuse", &island_ground_2.m_diffuse.x);
//            ImGui::SliderFloat3("island diffuse", &island_ground_2.m_diffuse.x, 0.0f, 1.0f);

            ImGui::SliderFloat("time", &t, 0.0f, 2.0f);

            glm::vec3 m_position = camera->m_position;
            ImGui::SliderFloat3("m_position", &m_position.x, -10.0f, 10.0f);
            ImGui::SliderFloat3("stone pos", &island_small_floating_stone.m_position.x, -10.0f, 10.0f);

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