#pragma once

#include "mesh.h"
#include "shader.h"
#include "light.h"
#include "shapes/shapes.h"

extern Bridge* bridge;
extern Skybox* skybox;
extern Axes* axes;

extern Mesh* cube;
extern Mesh* sun_object;
extern Mesh* lamp_mesh;

extern DirectionalLight* sun;
extern PointLight* lamp;
extern SpotLight* flashlight;

extern Shader* phong_shader;
extern Shader* standard_shader;
extern Shader* water_shader;

extern Texture* texture;
extern Texture* sun_texture;

class Configuration {
public:
    Configuration();

    virtual ~Configuration();

};