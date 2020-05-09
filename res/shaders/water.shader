#shader vertex
#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_texture;


out vec3 f_position;
out vec3 f_normal;
out vec2 f_tex_coord;
out vec3 eye_direction_cameraspace;

uniform mat4 u_M;
uniform mat4 u_VP;
uniform float u_time;


void main()
{
    f_normal = mat3(u_M) * v_normal;

    // Vector that goes from the vertex to the camera, in camera space.
    // In camera space, the camera is at the origin (0,0,0).
    vec3 v_position_cameraspace = (u_VP * vec4(v_position, 1)).xyz;
    eye_direction_cameraspace = vec3(0, 0, 0) - v_position_cameraspace;
    f_tex_coord = v_texture;
    f_position = vec3(u_M * vec4(v_position * u_time, 1.0));
    gl_Position = u_VP * vec4(f_position, 1.0);
}

#shader fragment
#version 330 core

out vec4 f_color;

in vec3 f_position;
in vec3 f_normal;
in vec2 f_tex_coord;
in vec3 eye_direction_cameraspace;

uniform vec3 u_camera_position;
uniform samplerCube u_skybox;
uniform sampler2D u_water_tex;

uniform bool fog;
uniform float fog_density = 0.1f;
uniform float u_bias = 0.0f;

uniform float u_refraction = 1.33f; // 1.00 for air, 1.33 for water

void main()
{
    float ratio = 1.00 / u_refraction;
    vec3 I = normalize(f_position - u_camera_position);
    vec3 N = normalize(f_normal);
    vec4 refracted_color = texture(u_skybox, refract(I, N, ratio));
    vec4 reflected_color = texture(u_skybox, reflect(I, N));
    vec4 water_tex_color = texture(u_water_tex, vec2(f_tex_coord.x - u_bias / 2, f_tex_coord.y + u_bias));
    vec4 mix_colors = mix(reflected_color, refracted_color, 0.5);
    f_color = mix(vec4(0, 0.1, 0.3, 0.3), mix_colors, 0.5);
    if (fog) {
        float d = distance(eye_direction_cameraspace, f_position);
        f_color = mix(f_color, vec4(0.5, 0.5, 0.5, 1), 1 - exp(- (d * fog_density)));
    }
    f_color = mix(f_color, water_tex_color, 0.2);
}
