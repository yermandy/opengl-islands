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
Mesh* fire = nullptr;
Mesh* menu_bar = nullptr;
// endregion


// region light sources
DirectionalLight* sun = nullptr;
PointLight* lamp = nullptr;
PointLight* campfire = nullptr;
SpotLight* flashlight = nullptr;
// endregion


// region shaders
Shader* phong_shader = nullptr;
Shader* standard_shader = nullptr;
Shader* water_shader = nullptr;
Shader* animation_shader = nullptr;
// endregion


// region textures
Texture* texture = nullptr;
Texture* sun_texture = nullptr;
Texture* fire_texture = nullptr;
Texture* water_texture = nullptr;
Texture* menu_fog_on = nullptr;
Texture* menu_fog_off = nullptr;
Texture* menu_sunlight_on = nullptr;
Texture* menu_sunlight_off = nullptr;
Texture* menu_flashlight_on = nullptr;
Texture* menu_flashlight_off = nullptr;
Texture* menu_skybox_day = nullptr;
Texture* menu_skybox_night = nullptr;
// endregion


// region curves
Hermite* hermite_curve = nullptr;
// endregion


bool island_moving = false;
bool clouds_moving = false;
bool sun_shines = true;
bool flame_burns = true;
bool main_menu = false;


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

    Mesh* lamp_light = new Mesh("res/objects/lamp/lamp_light.obj", island_position);
    Mesh* lamp_stone = new Mesh("res/objects/lamp/lamp_stone.obj", island_position);
    Mesh* lamp_stone_2 = new Mesh("res/objects/lamp/lamp_stone_2.obj", island_position);
    Mesh* lamp_wood = new Mesh("res/objects/lamp/lamp_wood.obj", island_position);

    Mesh* island_2_grass = new Mesh("res/objects/island_2/island_2_grass.obj", island_position);
    Mesh* island_2_snow = new Mesh("res/objects/island_2/island_2_snow.obj", island_position);
    Mesh* island_2_snow_floor = new Mesh("res/objects/island_2/island_2_snow_floor.obj", island_position);
    Mesh* island_2_stone = new Mesh("res/objects/island_2/island_2_stone.obj", island_position);
    Mesh* island_2_tree_leaves = new Mesh("res/objects/island_2/island_2_tree_leaves.obj", island_position);
    Mesh* island_2_tree_wood = new Mesh("res/objects/island_2/island_2_tree_wood.obj", island_position);
    Mesh* island_2_clouds = new Mesh("res/objects/island_2/island_2_clouds.obj", island_position);

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

    island->push_back(lamp_light);
    island->push_back(lamp_stone);
    island->push_back(lamp_stone_2);
    island->push_back(lamp_wood);

    island->push_back(island_2_grass);
    island->push_back(island_2_snow);
    island->push_back(island_2_snow_floor);
    island->push_back(island_2_stone);
    island->push_back(island_2_tree_leaves);
    island->push_back(island_2_tree_wood);
    island->push_back(island_2_clouds);

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
    island_water = new Mesh("res/objects/island/island_water_1.obj", island_position);
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

    fire = new Mesh("res/objects/fire/fire.obj", island_position);
    menu_bar = new Mesh("res/objects/menu_bar.obj");
    // endregion


    // region light sources
    sun = new DirectionalLight(glm::vec3(1.0f),
                               glm::vec3(1.0f),
                               glm::vec3(1.0f),
                               glm::vec3(0.0f));

    lamp = new PointLight(glm::vec3(0.1f),
                          glm::vec3(1.0f),
                          glm::vec3(1.0f),
                          glm::vec3(2.432f, -3.7f, 0.295f),
                          0.015f,
                          0.26f,
                          0.15f);

    campfire = new PointLight(glm::vec3(0.1f),
                              glm::vec3(1.0f),
                              glm::vec3(1.0f),
                              glm::vec3(-10.0f, -5.23f, 20.3f),
                              0.015f,
                              0.1f,
                              0.15f);

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
    // setup point light (lamp)
    phong_shader->SetVec3("point_lights[0].position", lamp->m_position);
    phong_shader->SetVec3("point_lights[0].ambient", lamp->m_ambient);
    phong_shader->SetVec3("point_lights[0].diffuse", lamp->m_diffuse);
    phong_shader->SetVec3("point_lights[0].specular", lamp->m_specular);
    phong_shader->SetFloat1("point_lights[0].constant", lamp->m_constant);
    phong_shader->SetFloat1("point_lights[0].linear", lamp->m_linear);
    // setup point light (campfire)
    phong_shader->SetVec3("point_lights[1].position", campfire->m_position);
    phong_shader->SetVec3("point_lights[1].ambient", campfire->m_ambient);
    phong_shader->SetVec3("point_lights[1].diffuse", campfire->m_diffuse);
    phong_shader->SetVec3("point_lights[1].specular", campfire->m_specular);
    phong_shader->SetFloat1("point_lights[1].constant", campfire->m_constant);
    phong_shader->SetFloat1("point_lights[1].linear", campfire->m_linear);
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


    animation_shader = new Shader("res/shaders/animation.shader");
    // endregion


    // region textures
    texture = new Texture("res/textures/cloud_texture.jpg");
    sun_texture = new Texture("res/textures/sun_texture.jpg");
    fire_texture = new Texture("res/textures/fire.jpg");
    water_texture = new Texture("res/textures/water.jpg");

    menu_fog_on = new Texture("res/textures/menu/fog_on.png");
    menu_fog_off = new Texture("res/textures/menu/fog_off.png");
    menu_sunlight_on = new Texture("res/textures/menu/sunlight_on.png");
    menu_sunlight_off = new Texture("res/textures/menu/sunlight_off.png");
    menu_flashlight_on = new Texture("res/textures/menu/flashlight_on.png");
    menu_flashlight_off = new Texture("res/textures/menu/flashlight_off.png");
    menu_skybox_day = new Texture("res/textures/menu/skybox_day.png");
    menu_skybox_night = new Texture("res/textures/menu/skybox_night.png");
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
