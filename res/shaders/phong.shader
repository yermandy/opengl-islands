#shader vertex
#version 330 core

layout(location = 0) in vec3 v_position; // vertex position in world space
layout(location = 1) in vec3 v_normal;   // vertex normal
layout(location = 2) in vec2 v_texture;  // vetrex texture coordinates


uniform mat4 u_MPV;
uniform mat4 u_M;
uniform mat4 u_V;
uniform vec3 u_light_position;


// Output data that will be interpolated for each fragment
//out vec2 UV;
out vec3 v_position_worldspace;
out vec3 v_normal_cameraspace;
out vec3 eye_direction_cameraspace;
out vec3 light_direction_cameraspace;
//out vec3 fragment_color;


void main() {

    // Output position of the vertex, in clip space : MVP * position
    gl_Position = u_MPV * vec4(v_position, 1);

    // Position of the vertex, in worldspace : M * position
    v_position_worldspace = (u_M * vec4(v_position, 1)).xyz;

    // Vector that goes from the vertex to the camera, in camera space.
    // In camera space, the camera is at the origin (0,0,0).
    vec3 v_position_cameraspace = (u_V * u_M * vec4(v_position, 1)).xyz;
    eye_direction_cameraspace = vec3(0, 0, 0) - v_position_cameraspace;

    // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
    vec3 light_position_cameraspace = (u_V * vec4(u_light_position, 1)).xyz;
    light_direction_cameraspace = light_position_cameraspace + eye_direction_cameraspace;

    // Normal of the the vertex, in camera space
    // Only correct if u_M does not scale the model ! Use its inverse transpose if not.
    v_normal_cameraspace = (u_V * u_M * vec4(v_normal, 0)).xyz;

    // UV of the vertex. No special space for this one.
//    UV = vertexUV;
}

#shader fragment
#version 330 core

layout(location = 0) out vec3 color;

// structure that describes currently used material
struct Material {
    vec3  ambient;     // ambient component
    vec3  diffuse;     // diffuse component
    vec3  specular;    // specular component
    float shininess;   // sharpness of specular reflection
    bool  use_texture; // defines whether the texture is used or not
};

// sampler for the texture access
uniform sampler2D u_tex_coords;
uniform Material u_material;
uniform vec3 u_light_position;
uniform vec3 light_color = vec3(1);
uniform float light_power = 100;

in vec3 v_position_worldspace;
in vec3 v_normal_cameraspace;
in vec3 eye_direction_cameraspace;
in vec3 light_direction_cameraspace;
//in vec3 fragment_color;


void main() {

    vec3 MaterialDiffuseColor = vec3(0.15, 0.4, 0.1);
    vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);
    // Distance to the light
    float distance = length(u_light_position - v_position_worldspace);

    // Normal of the computed fragment, in camera space
    vec3 n = normalize(v_normal_cameraspace);
    // Direction of the light (from the fragment to the light)
    vec3 l = normalize(light_direction_cameraspace);
    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float cosTheta = clamp(dot(n, l), 0, 1);

    // Eye vector (towards the camera)
    vec3 E = normalize(eye_direction_cameraspace);
    // Direction in which the triangle reflects the light
    vec3 R = reflect(-l, n);
    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cosAlpha = clamp(dot(E, R), 0, 1);

    // Ambient : simulates indirect lighting
    color += MaterialAmbientColor;
    // Diffuse : "color" of the object
    color += MaterialDiffuseColor * light_color * light_power * cosTheta  / (distance * distance);
    // Specular : reflective highlight, like a mirror
    color += MaterialSpecularColor * light_color * light_power * pow(cosAlpha, 5) / (distance * distance);

//    color = u_material.ambient;
}
