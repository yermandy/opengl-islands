#shader vertex
#version 330 core

// vetrex position in world space
//layout(location = 0) in vec3 v_position;
// vetrex color
//layout(location = 1) in vec3 v_color;

layout(location = 0) in vec3 v_position; // vertex position in world space
layout(location = 1) in vec3 v_normal;   // vertex normal / color
layout(location = 2) in vec2 v_texture;  // vetrex texture coordinates

uniform mat4 u_MVP;

out vec3 fragment_color;
out vec2 v_uv;

void main() {
    gl_Position = u_MVP * vec4(v_position, 1.0f);
    fragment_color = v_normal;
    v_uv = v_texture;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_tex_sampler;
uniform bool u_use_texture;

// interpolated fragment color (or normals)
in vec3 fragment_color;
// interpolated vertex texture coordinates
in vec2 v_uv;

void main() {
    if (u_use_texture)
        color = texture(u_tex_sampler, v_uv);
    else
        color = vec4(fragment_color, 1.0f);
}
