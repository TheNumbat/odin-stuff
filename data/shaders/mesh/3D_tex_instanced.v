
#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 v_texcoord;

// instanced
layout (location = 2) in vec3 offset;

uniform mat4 transform;

out vec2 f_texcoord;

void main() {
	gl_Position = transform * vec4(pos + offset, 1.0);
	f_texcoord = v_texcoord;
}
