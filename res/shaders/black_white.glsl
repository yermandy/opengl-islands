#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
//layout(location = 1) in vec3 vertex_color;

uniform mat4 u_MVP;
//out vec3 fragment_color;

void main() {
    gl_Position = u_MVP * position;
//    fragmentColor =  vertex_color;
//    gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
//in vec3 fragment_color;
//uniform vec4 u_color;

void main() {
//    color = vec4(fragment_color, 1.0f);
    color = vec4(1.0f);
}
