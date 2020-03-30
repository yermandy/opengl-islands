#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_vertex_color;

uniform mat4 u_MPV;
//uniform mat4 u_view_proj;
//uniform mat4 u_transform;

out vec3 fragment_color;


void main() {
    gl_Position = u_MPV * a_position;
    fragment_color =  a_vertex_color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragment_color;

void main() {
    color = vec4(fragment_color, 1.0f);
}
