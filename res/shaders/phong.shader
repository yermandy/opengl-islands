#shader vertex
#version 330 core

layout(location = 0) in vec3 v_position; // vertex position in world space
layout(location = 1) in vec3 v_normal;   // vertex normal
layout(location = 2) in vec2 v_texture;  // vetrex texture coordinates


uniform mat4 u_MVP;
uniform mat4 u_M;
uniform mat4 u_V;
//uniform vec3 u_light_position;


// Output data that will be interpolated for each fragment
//out vec2 UV;
out vec3 v_position_worldspace;
out vec3 v_normal_cameraspace;
out vec2 v_uv;
out vec3 eye_direction_cameraspace;
//out vec3 light_direction_cameraspace;

void main() {

    // Output position of the vertex, in clip space : MVP * position
    gl_Position = u_MVP * vec4(v_position, 1);

    // Position of the vertex, in worldspace : M * position
    v_position_worldspace = (u_M * vec4(v_position, 1)).xyz;

    // Vector that goes from the vertex to the camera, in camera space.
    // In camera space, the camera is at the origin (0,0,0).
    vec3 v_position_cameraspace = (u_V * u_M * vec4(v_position, 1)).xyz;
    eye_direction_cameraspace = vec3(0, 0, 0) - v_position_cameraspace;

    // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
//    vec3 light_position_cameraspace = (u_V * vec4(u_light_position, 1)).xyz;
//    light_direction_cameraspace = light_position_cameraspace + eye_direction_cameraspace;

    // Normal of the the vertex, in camera space
//    v_normal_cameraspace = (u_V * u_M * vec4(v_normal, 0)).xyz;
    v_normal_cameraspace = (transpose(inverse(u_V * u_M)) * vec4(v_normal, 0)).xyz;


    // UV of the vertex. No special space for this one.
    v_uv = v_texture;
}

#shader fragment
#version 330 core

layout(location = 0) out vec3 color = vec3(0.0f);

// structure that describes currently used material
struct Material {
    vec3  ambient;     // ambient component
    vec3  diffuse;     // diffuse component
    vec3  specular;    // specular component
    float shininess;   // sharpness of specular reflection
    bool  use_texture; // defines whether the texture is used or not
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// sampler for the texture access
uniform sampler2D u_tex_sampler;
uniform Material u_material;
uniform Material u_light;
//uniform vec3 u_light_position;
uniform vec3 light_color = vec3(1);
uniform float light_power = 100;

#define N_POINT_LIGHTS 1
uniform PointLight point_lights[N_POINT_LIGHTS];
uniform DirectionalLight sun;

in vec3 v_position_worldspace;
in vec3 v_normal_cameraspace;
in vec3 eye_direction_cameraspace;
in vec2 v_uv;
//in vec3 light_direction_cameraspace;

//uniform vec3 light_direction_cameraspace;


vec3 GetPointLight(PointLight light, vec3 N, vec3 fragment_position, vec3 E)
{
    // Direction of the light (from the fragment to the light)
    vec3 L = normalize(light.position - fragment_position);
    // Cosine of the angle between the normal and the light direction,
    float cos_alpha = max(dot(N, L), 0.0);
    // Direction in which the triangle reflects the light
    vec3 R = reflect(-L, N);
    // Cosine of the angle between the viewer and the reflected light
    float cos_beta = max(dot(E, R), 0);
    // distance to the light source and attenuation
    float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

//    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoords));
//    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // Combine ambient, diffuse and specular to recieve Phong shading
    vec3 ambient  = light.ambient * u_material.ambient;
    vec3 diffuse  = light.diffuse * cos_alpha * u_material.diffuse;
    vec3 specular = light.specular * pow(cos_beta, u_material.shininess) * u_material.specular;
    return (ambient + diffuse + specular) * attenuation;
}

vec3 GetDirectionalLight(DirectionalLight light, vec3 N, vec3 E) {
    // Direction of the light (from the fragment to the light)
    vec3 L = normalize(light.direction);
    // Cosine of the angle between the normal and the light direction,
    float cos_alpha = max(dot(N, L), 0);
    // Direction in which the triangle reflects the light
    vec3 R = reflect(-L, N);
    // Cosine of the angle between the viewer and the reflected light
    float cos_beta = max(dot(E, R), 0);
    // Ambient : indirect lighting simulation
    vec3 ambient = u_material.ambient * u_light.ambient;
    // Diffuse : represents a directional light cast by a light source
    vec3 diffuse = cos_alpha * u_material.diffuse * u_light.diffuse;
    // Specular : reflective highlight, mirror like property
    vec3 specular = pow(cos_beta, u_material.shininess) * u_material.specular * u_light.specular;
    // Combine ambient, diffuse and specular to recieve Phong shading
    return ambient + diffuse + specular;
}


void main() {
    // Normal of the computed fragment, in camera space
    vec3 N = normalize(v_normal_cameraspace);
    // Eye vector (towards the camera)
    vec3 E = normalize(eye_direction_cameraspace);
    // Add directional light (sun)
    color += GetDirectionalLight(sun, N, E);
    // Add all point light sources
    for (int i = 0; i < N_POINT_LIGHTS; i++)
        color += GetPointLight(point_lights[i], N, v_position_worldspace, E);

    if (u_material.use_texture)
        color *= texture(u_tex_sampler, v_uv).rgb;
}