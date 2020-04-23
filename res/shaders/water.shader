#shader vertex
#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;

out vec3 v_tex_coord;

out vec3 f_normal;
out vec3 f_position;

uniform mat4 u_M;
uniform mat4 u_V;
uniform mat4 u_P;

void main()
{
    f_normal = mat3(transpose(inverse(u_M))) * v_normal;
    f_position = vec3(u_M * vec4(v_position, 1.0));
    gl_Position = u_P * u_V * vec4(f_position, 1.0);
}

#shader fragment
#version 330 core

out vec4 f_color;

in vec3 f_normal;
in vec3 f_position;

uniform vec3 u_camera_position;
uniform samplerCube u_skybox;

void main()
{
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(f_position - u_camera_position);
    vec3 R = refract(I, normalize(f_normal), ratio);
    f_color = vec4(texture(u_skybox, R).rgb, 1.0) * vec4(0.0f, 0.1f, 0.5f, 1.0f) * 2.0f;
}
