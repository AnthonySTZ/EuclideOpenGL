#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 projection;
uniform mat4 view;

out vec3 vertexColor;

void main() {
	vec4 positionWorld = vec4(aPos, 1.0);
	gl_Position = projection * (view * positionWorld);
	vertexColor = aColor;

}