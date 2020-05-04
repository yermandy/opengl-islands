#include "configuration.h"
#include "camera.h"


// region objects
Bridge* bridge = nullptr;
Skybox* skybox = nullptr;
Axes* axes = nullptr;
// endregion


// region meshes
Mesh* cube = nullptr;
Mesh* sun_object = nullptr;
Mesh* lamp_mesh = nullptr;
// endregion


// region light sources
DirectionalLight* sun = nullptr;
PointLight* lamp = nullptr;
SpotLight* flashlight = nullptr;
// endregion


// region shaders
Shader* phong_shader = nullptr;
Shader* standard_shader = nullptr;
Shader* water_shader = nullptr;
// endregion


// region textures
Texture* texture = nullptr;
Texture* sun_texture = nullptr;
// endregion


Configuration::Configuration() {
    Camera* camera = Camera::GetInstance();

    // region objects
    bridge = new Bridge();
    skybox = new Skybox();
    // endregion

    // region meshes
    cube = new Mesh("res/objects/cube.obj");
    sun_object = new Mesh("res/objects/sun.obj");
    lamp_mesh = new Mesh("res/objects/cube.obj", glm::vec3(0.0f, -5.0f, 0.0f));
    // endregion


    // region light sources
    sun = new DirectionalLight(glm::vec3(1.0f),
                               glm::vec3(1.0f),
                               glm::vec3(1.0f),
                               glm::vec3(0.0f));

    lamp = new PointLight(glm::vec3(0.1f),
                          glm::vec3(1.0f),
                          glm::vec3(1.0f),
                          glm::vec3(0.0f, -3.0f, 1.5f));

    flashlight = new SpotLight(glm::vec3(0.2f),
                               glm::vec3(1.0f),
                               glm::vec3(1.0f),
                               glm::vec3(0.0f),
                               glm::vec3(0.0f),
                               glm::cos(glm::radians(12.5f)),
                               glm::cos(glm::radians(13.0f)),
                               50,
                               false);
    camera->flashlight = flashlight;
    // endregion


    // region shaders
    phong_shader = new Shader("res/shaders/phong.shader");
    phong_shader->Bind();
    // setup ambient light
    phong_shader->SetVec3("u_light.ambient", glm::vec3(0.1f));
    phong_shader->SetVec3("u_light.diffuse", glm::vec3(0.7f));
    phong_shader->SetVec3("u_light.specular", glm::vec3(1.0f));
    // setup point light
    phong_shader->SetVec3("point_lights[0].position", lamp->m_position);
    phong_shader->SetVec3("point_lights[0].ambient", lamp->m_ambient);
    phong_shader->SetVec3("point_lights[0].diffuse", lamp->m_diffuse);
    phong_shader->SetVec3("point_lights[0].specular", lamp->m_specular);
    phong_shader->SetFloat1("point_lights[0].constant", lamp->m_constant);
    phong_shader->SetFloat1("point_lights[0].linear", .2f);
    // setup spot light
    phong_shader->SetVec3("flashlight.position", flashlight->m_position);
    phong_shader->SetVec3("flashlight.direction", flashlight->m_direction);
    phong_shader->SetVec3("flashlight.ambient", flashlight->m_ambient);
    phong_shader->SetVec3("flashlight.diffuse", flashlight->m_diffuse);
    phong_shader->SetVec3("flashlight.specular", flashlight->m_specular);
    phong_shader->SetFloat1("flashlight.cut_off", flashlight->m_cut_off);
    phong_shader->SetFloat1("flashlight.exponent", flashlight->m_exponent);
    phong_shader->SetFloat1("flashlight.constant", flashlight->m_constant);
    phong_shader->SetFloat1("flashlight.linear", flashlight->m_linear);
    phong_shader->SetFloat1("flashlight.quadratic", flashlight->m_quadratic);
    phong_shader->Unbind();

    standard_shader = new Shader("res/shaders/standard.shader");

    water_shader = new Shader("res/shaders/water.shader");
    // endregion


    // region textures
    texture = new Texture("res/textures/cloud_texture.jpg");
    sun_texture = new Texture("res/textures/sun_texture.jpg");
    // endregion
}

Configuration::~Configuration() {
//    delete cube;
//    delete sun_object;
//    delete lamp_mesh;
//
//    delete sun;
//    delete lamp;
//    delete flashlight;
//
//    delete phong_shader;
//    delete standard_shader;
//    delete water_shader;
}
