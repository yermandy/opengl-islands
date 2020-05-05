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

extern DirectionalLight* sun;
extern PointLight* lamp;
extern SpotLight* flashlight;

extern Shader* phong_shader;
extern Shader* standard_shader;
extern Shader* water_shader;

extern Texture* texture;
extern Texture* sun_texture;

extern Hermite* hermite_curve;

class Configuration {
public:
    Configuration();

    virtual ~Configuration();

};