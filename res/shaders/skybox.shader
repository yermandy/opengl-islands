#shader vertex
#version 330 core
layout (location = 0) in vec2 v_position;

out vec3 v_tex_coord;

uniform mat4 u_inv_PV;

void main()
{
    vec4 position = vec4(v_position, 0.9999, 1.0);
    vec4 world_view_coord = u_inv_PV * position;
    v_tex_coord = world_view_coord.xyz / world_view_coord.w;
    gl_Position = position;
}

#shader fragment
#version 330 core

out vec4 color;

in vec3 v_tex_coord;

uniform bool fog;
uniform samplerCube u_skybox;

void main()
{
    color = texture(u_skybox, v_tex_coord);
    if (fog)
        color = vec4(0.5, 0.5, 0.5, 1);
}
