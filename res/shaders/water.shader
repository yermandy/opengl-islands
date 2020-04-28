#shader vertex
#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;

out vec3 v_tex_coord;

out vec3 f_normal;
out vec3 f_position;

uniform mat4 u_M;
uniform mat4 u_VP;
uniform float u_time;


void main()
{
    f_normal = mat3(u_M) * v_normal;

    f_position = vec3(u_M * vec4(v_position * u_time, 1.0));
    gl_Position = u_VP * vec4(f_position, 1.0);
}

#shader fragment
#version 330 core

out vec4 f_color;

in vec3 f_normal;
in vec3 f_position;

uniform vec3 u_camera_position;
uniform samplerCube u_skybox;

uniform float u_refraction = 1.33f; // 1.00 for air, 1.33 for water

void main()
{
    float ratio = 1.00 / u_refraction;
    vec3 I = normalize(f_position - u_camera_position);
    vec3 N = normalize(f_normal);
    vec4 refracted_color = texture(u_skybox, refract(I, N, ratio));
    vec4 reflected_color = texture(u_skybox, reflect(I, N));
    vec4 mix_colors = mix(reflected_color, refracted_color, 0.5);
    f_color = mix(vec4(0, 0.1, 0.3, 0.3), mix_colors, 0.5);
}
