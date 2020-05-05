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
Mesh* island_water = nullptr;
Mesh* island_bridge = nullptr;
Mesh* island_small_floating_stone = nullptr;
std::vector<Mesh*>* island = nullptr;
std::vector<Mesh*>* island_clouds = nullptr;
Mesh* button_1 = nullptr;
Mesh* button_2 = nullptr;
Mesh* button_3 = nullptr;
std::vector<Mesh*>* buttons = nullptr;
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


// region curves
Hermite* hermite_curve = nullptr;
// endregion


bool island_moving = false;
bool clouds_moving = false;


Configuration::Configuration() {
    Camera* camera = Camera::GetInstance();

    // region meshes
    cube = new Mesh("res/objects/cube.obj");
    sun_object = new Mesh("res/objects/sun.obj");
    lamp_mesh = new Mesh("res/objects/cube.obj", glm::vec3(0.0f, -5.0f, 0.0f));

    glm::vec3 island_position = glm::vec3(0.0f, -8.0f, 0.0f);

    // initialize island
    Mesh* island_ground_1 = new Mesh("res/objects/island/island_ground_1.obj", island_position);
    Mesh* island_ground_2 = new Mesh("res/objects/island/island_ground_2.obj", island_position);
    Mesh* island_mountains = new Mesh("res/objects/island/island_mountains.obj", island_position);
    Mesh* island_grass = new Mesh("res/objects/island/island_grass.obj", island_position);
    Mesh* island_red_gates = new Mesh("res/objects/island/island_red_gates.obj", island_position);
    Mesh* island_black_gates = new Mesh("res/objects/island/island_black_gates.obj", island_position);
    Mesh* island_stone_lamps = new Mesh("res/objects/island/island_stone_lamps.obj", island_position);
    Mesh* island_trees_wood = new Mesh("res/objects/island/island_trees_wood.obj", island_position);
    Mesh* island_leaves_1 = new Mesh("res/objects/island/island_leaves_1.obj", island_position);
    Mesh* island_leaves_2 = new Mesh("res/objects/island/island_leaves_2.obj", island_position);
    Mesh* island_leaves_3 = new Mesh("res/objects/island/island_leaves_3.obj", island_position);

    island = new std::vector<Mesh*>();
    island->push_back(island_ground_1);
    island->push_back(island_ground_2);
    island->push_back(island_mountains);
    island->push_back(island_grass);
    island->push_back(island_red_gates);
    island->push_back(island_black_gates);
    island->push_back(island_stone_lamps);
    island->push_back(island_trees_wood);
    island->push_back(island_leaves_1);
    island->push_back(island_leaves_2);
    island->push_back(island_leaves_3);

    // initialize clouds
    Mesh* island_cloud_1 = new Mesh("res/objects/island/island_cloud_1.obj", island_position);
    Mesh* island_cloud_2 = new Mesh("res/objects/island/island_cloud_2.obj", island_position);
    Mesh* island_cloud_3 = new Mesh("res/objects/island/island_cloud_3.obj", island_position);
    Mesh* island_cloud_4 = new Mesh("res/objects/island/island_cloud_4.obj", island_position);

    island_clouds = new std::vector<Mesh*>();
    island_clouds->push_back(island_cloud_1);
    island_clouds->push_back(island_cloud_2);
    island_clouds->push_back(island_cloud_3);
    island_clouds->push_back(island_cloud_4);

    // initialize all other meshes
    island_water = new Mesh("res/objects/island/island_water.obj", island_position);
    island_bridge = new Mesh("res/objects/island/island_bridge.obj", island_position,
                             glm::vec3(1.1f, 1.0f, 1.1f));
    island_small_floating_stone = new Mesh("res/objects/island/island_small_floating_stone.obj", island_position);

    // initialize action buttons
    button_1 = new Mesh("res/objects/buttons/button_1.obj", island_position);
    button_2 = new Mesh("res/objects/buttons/button_2.obj", island_position);
    button_3 = new Mesh("res/objects/buttons/button_3.obj", island_position);

    buttons = new std::vector<Mesh*>();
    buttons->push_back(button_1);
    buttons->push_back(button_2);
    buttons->push_back(button_3);
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


    // region objects
    bridge = new Bridge();
    skybox = new Skybox();
    axes = new Axes();
    // endregion


    // region curves
    hermite_curve = new Hermite(
            {
                    {0.0f,  0.0f, 0.0f},
                    {-5.0f, 0.0f, 4.0f},
                    {3.0f,  0.0f, 5.0f},
                    {7.0f,  0.0f, 6.0f},
                    {4.0f,  0.0f, 8.0f},
                    {0.0f,  0.0f, 6.0f},
                    {3.0f,  0.0f, 5.0f},
                    {5.0f,  0.0f, 2.0f},
                    {0.0f,  0.0f, 0.0f},
                    {-5.0f, 0.0f, 4.0f}
            });
    // endregion
}

Configuration::~Configuration() {}
