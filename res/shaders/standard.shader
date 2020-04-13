#shader vertex
#version 330 core

// vetrex position in world space
layout(location = 0) in vec3 v_position;
// vetrex color
layout(location = 1) in vec3 v_color;

uniform mat4 u_MPV;

out vec3 fragment_color;

void main() {
    gl_Position = u_MPV * vec4(v_position, 1.0f);
    fragment_color = v_color;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

// interpolated fragment color
in vec3 fragment_color;

void main() {
    color = vec4(fragment_color, 1.0f);
}
