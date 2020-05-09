#pragma once

#include "mesh.h"
#include "shader.h"
#include "light.h"
#include "shapes/shapes.h"
#include "curve.h"

extern Bridge* bridge;
extern Skybox* skybox;
extern Axes* axes;

extern Mesh* cube;
extern Mesh* sun_object;
extern Mesh* lamp_mesh;
extern Mesh* island_water;
extern Mesh* island_bridge;
extern Mesh* island_small_floating_stone;
extern std::vector<Mesh*>* island;
extern std::vector<Mesh*>* island_clouds;
extern Mesh* button_1;
extern Mesh* button_2;
extern Mesh* button_3;
extern std::vector<Mesh*>* buttons;
extern Mesh* fire;

extern DirectionalLight* sun;
extern PointLight* lamp;
extern PointLight* campfire;
extern SpotLight* flashlight;

extern Shader* phong_shader;
extern Shader* standard_shader;
extern Shader* water_shader;
extern Shader* animation_shader;

extern Texture* texture;
extern Texture* sun_texture;
extern Texture* fire_texture;

extern Hermite* hermite_curve;

extern bool island_moving;
extern bool clouds_moving;
extern bool sun_shines;
extern bool flame_burns;

class Configuration {
public:
    Configuration();

    virtual ~Configuration();

};