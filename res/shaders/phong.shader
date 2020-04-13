#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;           // vertex position in world space
layout(location = 1) in vec3 a_normal;             // vertex normal
layout(location = 2) in vec2 a_texture;            // incoming texture coordinates

uniform mat4 u_MPV;
//uniform mat4 u_view_proj;
//uniform mat4 u_transform;

out vec3 fragment_color;


void main() {
    gl_Position = u_MPV * vec4(a_position, 1);
    //    fragment_color =  a_vertex_color;
    fragment_color =  vec3(1.0);
}

    #shader fragment
    #version 330 core

layout(location = 0) out vec3 color;

in vec3 fragment_color;

void main() {
    color = fragment_color;
}
