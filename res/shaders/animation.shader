#shader vertex
#version 330 core

layout(location = 0) in vec3 v_position; // vertex position in world space
layout(location = 1) in vec3 v_normal;   // vertex normal / color
layout(location = 2) in vec2 v_texture;  // vetrex texture coordinates

uniform mat4 u_MVP;
uniform float u_frame;
uniform int u_frames_count = 51;

out vec3 fragment_color;
out vec2 v_uv;


void main() {
    gl_Position = u_MVP * vec4(v_position, 1.0f);
    fragment_color = v_normal;
    v_uv = v_texture;
    v_uv.x = v_uv.x / u_frames_count + u_frame / u_frames_count;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_tex_sampler;

// interpolated fragment color (or normals)
in vec3 fragment_color;
// interpolated vertex texture coordinates
in vec2 v_uv;

void main() {
    color = texture(u_tex_sampler, v_uv);
    if (color.x > 0.55 || color.y > 0.55 || color.z > 0.55)
        color.a = 1;
    else
        color.a = 0;
}
