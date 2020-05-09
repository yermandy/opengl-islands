#include <iostream>

#include "camera.h"
#include "window.h"
#include "renderer.h"
#include "configuration.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
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

    glm::vec3 translate;
    glm::mat4 M;

    Renderer renderer;

    Configuration configuration;

    do {
        renderer.Clear();

        camera->UpdateViewProjection();
        glm::mat4 P = camera->GetMatProj();
        glm::mat4 V = camera->GetMatView();
        glm::mat4 VP = P * V;

        static double last_time = glfwGetTime();

        double time = glfwGetTime();
        auto delta_time = float(time - last_time);

        // region Flashlight
        {
            phong_shader->Bind();
            phong_shader->SetInt1("flashlight.on", flashlight->m_on);
            if (flashlight->m_on) {
                flashlight->m_direction = camera->m_direction;
                flashlight->m_position = camera->m_position;

                phong_shader->SetVec3("flashlight.position", flashlight->m_position);
                phong_shader->SetVec3("flashlight.direction", flashlight->m_direction);
            }
        }
        // endregion


        // region Sun
        {
            sun->m_direction[0] = 5000 * glm::sin(time * .5);
            sun->m_direction[1] = 10000;
            sun->m_direction[2] = 5000 * glm::cos(time * .5);
            sun->m_direction = glm::vec4(sun->m_direction, 1);
            translate = glm::vec3(sun->m_direction[0] / 100, sun->m_direction[1] / 100, sun->m_direction[2] / 100);
            M = glm::translate(glm::mat4(1.0f), translate);
            M = glm::scale(M, glm::vec3(2.0f));
            M = glm::rotate(M, glm::radians(float(time) * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            standard_shader->Bind();
            sun_object->m_texture->Bind();
            standard_shader->SetInt1("u_tex_sampler", 0);
            standard_shader->SetInt1("u_use_texture", 1);
            standard_shader->SetMat4("u_MVP", VP * M);
            renderer.DrawTriangles(*sun_object->vao, *sun_object->ibo, *standard_shader);
        }
        // endregion


        // region Buttons
        {
            glEnable(GL_STENCIL_TEST);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            unsigned int picking_id = 0;
            for (auto button : *buttons) {
                glStencilFunc(GL_ALWAYS, ++picking_id, -1);
                M = glm::mat4(1.0f);
                M = glm::translate(M, button->m_position);
                M = glm::scale(M, button->m_scale);

                M = glm::translate(M, button->m_pivot);
                M = glm::rotate(M, glm::radians(float(time) * 30.0f), glm::vec3(0.5f, 1.0f - picking_id, 0.0f));
                M = glm::translate(M, -button->m_pivot);

                button->m_picking_id = picking_id;
                phong_shader->Bind();
                phong_shader->SetMVP(VP * M, M, V);
                phong_shader->SetMeshMaterial(*button);
                renderer.DrawTriangles(*button->vao, *button->ibo, *phong_shader);
            }

            glReadPixels(int(width / 2), int(height / 2), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE,
                         &camera->looking_at_object);

            camera->distance_to_picking_object = 0;

            if (camera->looking_at_object != 0) {
                Mesh* button = (*buttons)[camera->looking_at_object - 1];
                camera->distance_to_picking_object = glm::distance(button->m_pivot + button->m_position,
                                                                   camera->m_position);
            }

            glDisable(GL_STENCIL_TEST);
        }
        // endregion


        // region Bridge (manual element)
        {
            M = glm::mat4(1.0f);
            M = glm::translate(M, island_bridge->m_position);
            phong_shader->Bind();
            phong_shader->SetInt1("u_material.use_texture", 0);
            phong_shader->SetMVP(VP * M, M, V);
            phong_shader->SetMeshMaterial(*island_bridge);
            renderer.DrawTriangles(*bridge->vao, *bridge->ibo, *phong_shader);
        }
        // endregion


//        {
//            M = glm::translate(glm::mat4(1.0f), lamp->m_position);
//            M = glm::scale(M, glm::vec3(0.1f));
//            standard_shader->Bind();
//            standard_shader->SetInt1("u_use_texture", 0);
//            standard_shader->SetMat4("u_MVP", VP * M);
//            renderer.DrawTriangles(*lamp_mesh->vao, *lamp_mesh->ibo, *standard_shader);
//        }

        // region Island clouds
        {
            for (Mesh* cloud : *island_clouds) {
                M = glm::mat4(1.0f);
                M = glm::translate(M, cloud->m_position);
                if (clouds_moving) {
                    cloud->m_time += delta_time;
                    M = glm::rotate(M, glm::radians(float(cloud->m_time) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                }
                M = glm::scale(M, cloud->m_scale);
                phong_shader->Bind();
                phong_shader->SetInt1("u_material.use_texture", 0);
                phong_shader->SetMVP(VP * M, M, V);
                phong_shader->SetMeshMaterial(*cloud);
                renderer.DrawTriangles(*cloud->vao, *cloud->ibo, *phong_shader);
            }
        }
        // endregion


        // region Island
        {
            for (const Mesh* island_part : *island) {
                M = glm::mat4(1.0f);
                M = glm::translate(M, island_part->m_position);
                M = glm::scale(M, island_part->m_scale);
                phong_shader->Bind();
                phong_shader->SetInt1("u_material.use_texture", 0);
                phong_shader->SetMVP(VP * M, M, V);
                phong_shader->SetMeshMaterial(*island_part);
                renderer.DrawTriangles(*island_part->vao, *island_part->ibo, *phong_shader);
            }
        }
        // endregion

//        {
//            M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
//            M = glm::scale(M, glm::vec3(0.5f));
//            phong_shader->Bind();
//            phong_shader->SetMVP(VP * M, M, V);
//            renderer.DrawTriangles(*cube.vao, *cube.ibo, phong_shader);
//        }

        // region World axes
        {
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(10, 10, 160, 160);
            standard_shader->Bind();
            standard_shader->SetInt1("u_use_texture", 0);
            standard_shader->SetMat4("u_MVP", camera->GetDirections());
            renderer.DrawLines(*axes->vao, *axes->ibo, *standard_shader);
            glViewport(0, 0, width, height);
        }
        // endregion


        // region Skybox
        {
            skybox->shader->Bind();
            skybox->shader->SetInt1("u_skybox", 0);
            glm::mat4 inverse_PV = glm::inverse(P * glm::mat4(glm::mat3(V)));
            skybox->shader->SetMat4("u_inv_PV", inverse_PV);
            skybox->Draw();
        }
        // endregion


        // region Small island
        {
            if (island_moving) {
                island_small_floating_stone->m_time += delta_time;
                glm::vec3 point = hermite_curve->CalculatePosition(float(island_small_floating_stone->m_time / 3.0f));

                island_small_floating_stone->m_position[0] = point[0];
                island_small_floating_stone->m_position[2] = point[2];
            }

            M = glm::mat4(1.0f);
            M = glm::translate(M, island_small_floating_stone->m_position);
            M = glm::scale(M, island_small_floating_stone->m_scale);

            // Rotate small island
            M = glm::translate(M, island_small_floating_stone->m_pivot);
            M = glm::rotate(M, glm::radians(float(time) * 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            M = glm::translate(M, -island_small_floating_stone->m_pivot);

            phong_shader->Bind();
            phong_shader->SetInt1("u_material.use_texture", 0);
            phong_shader->SetMVP(VP * M, M, V);
            phong_shader->SetMeshMaterial(*island_small_floating_stone);
            renderer.DrawTriangles(*island_small_floating_stone->vao, *island_small_floating_stone->ibo, *phong_shader);
        }

        // endregion

//        {
//            M = glm::translate(glm::mat4(1.0f), point);
//            M = glm::scale(M, glm::vec3(0.5f));
//            phong_shader->Bind();
//            phong_shader->SetMVP(VP * M, M, V);
//            renderer.DrawTriangles(*island_small_floating_stone->vao, *island_small_floating_stone->ibo, phong_shader);
//        }

        /*
//         water cube
        {
            LOG(glEnable(GL_BLEND));
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            water_shader->Bind();
            water_shader->SetVec3("u_camera_position", camera->GetPosition());
            M = glm::mat4(1.0f);
//            M = glm::translate(M, glm::vec3(0.0f, 0.0f, 3.0f));
//            M = glm::rotate(M, glm::radians(float(time) * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//            M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
            water_shader->SetMat4("u_M", M);
            water_shader->SetMat4("u_VP", VP);

            skybox->BindTexture();
            water_shader->SetInt1("u_skybox", 0);

            water_texture->Bind(1);
            water_shader->SetInt1("u_water_tex", 1);

            renderer.DrawTriangles(*cube->vao, *cube->ibo, *water_shader);
            LOG(glDisable(GL_BLEND));
        }
//         */


        // region Water
        {
            LOG(glEnable(GL_BLEND));
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            water_shader->Bind();
            M = glm::mat4(1.0f);
            M = glm::translate(M, island_water->m_position);
            M = glm::scale(M, island_water->m_scale);
            water_shader->SetVec3("u_camera_position", camera->GetPosition());
            water_shader->SetMat4("u_M", M);
            water_shader->SetMat4("u_VP", VP);

            skybox->BindTexture();
            water_shader->SetInt1("u_skybox", 0);

            water_texture->Bind(1);
            water_shader->SetInt1("u_water_tex", 1);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            water_shader->SetFloat1("u_bias", time / 10);

            water_shader->SetFloat1("u_time", std::cos(std::cos(float(time)) / 6));
            renderer.DrawTriangles(*island_water->vao, *island_water->ibo, *water_shader);
            LOG(glDisable(GL_BLEND));
        }
        // endregion

        // region Campfire
        if (flame_burns) {
            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            animation_shader->Bind();
            int frame = glm::abs(glm::abs(int((-time + 50) * 30)) % 100 - 50);
            animation_shader->SetFloat1("u_frame", frame);
            fire_texture->Bind();
            animation_shader->SetInt1("u_tex_sampler", 0);
            M = glm::translate(glm::mat4(1.0f), fire->m_position);
            animation_shader->SetMat4("u_MVP", P * V * M);
            renderer.DrawTriangles(*fire->vao, *fire->ibo, *animation_shader);
            glDisable(GL_BLEND);
            // campfire light
            phong_shader->Bind();
            campfire->m_quadratic = glm::sin(time * 2) / 15 + 0.15;
            phong_shader->SetFloat1("point_lights[1].quadratic", campfire->m_quadratic);
        }
        // endregion


        // region ImGui window
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Debug");

            ImGui::SliderFloat3("light position", &lamp->m_position.x, -25.0f, 25.0f);

            ImGui::Separator();

//            ImGui::ColorPicker3("island diffuse", &island_ground_2.m_diffuse.x);
//            ImGui::SliderFloat3("island diffuse", &island_ground_2.m_diffuse.x, 0.0f, 1.0f);

//            ImGui::SliderFloat("time", &t, 0.0f, 2.0f);

//            glm::vec3 m_position = camera->m_position;
//            ImGui::SliderFloat3("m_position", &m_position.x, -20.0f, 20.0f);
//            ImGui::SliderFloat3("lamp->m_position", &campfire->m_position.x, -20.0f, 20.3f);
//            ImGui::SliderFloat("lamp->m_constant", &campfire->m_constant, 0.0f, 3.0f);
//            ImGui::SliderFloat("lamp->m_linear", &campfire->m_linear, 0.0f, 3.0f);
//            ImGui::SliderFloat("lamp->m_quadratic", &campfire->m_quadratic, 0.0f, 3.0f);

//            phong_shader->Bind();
//            phong_shader->SetVec3("point_lights[1].position", campfire->m_position);
//            phong_shader->SetVec3("point_lights[1].ambient", campfire->m_ambient);
//            phong_shader->SetVec3("point_lights[1].diffuse", campfire->m_diffuse);
//            phong_shader->SetVec3("point_lights[1].specular", campfire->m_specular);
//            phong_shader->SetFloat1("point_lights[1].constant", campfire->m_constant);
//            phong_shader->SetFloat1("point_lights[1].linear", campfire->m_linear);
//            campfire->m_quadratic = glm::sin(time * 2) / 15 + 0.15;
//            std::cout << campfire->m_quadratic << std::endl;
//            phong_shader->SetFloat1("point_lights[1].quadratic", campfire->m_quadratic);

            ImGui::Separator();


            ImGui::Separator();

            phong_shader->Bind();
            phong_shader->SetVec3("point_lights[0].position", lamp->m_position);
            phong_shader->SetVec3("sun.direction", V * glm::vec4(sun->m_direction, 1.0f));

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        // endregion

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        last_time = time;

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && !glfwWindowShouldClose(window));


    return 0;
}