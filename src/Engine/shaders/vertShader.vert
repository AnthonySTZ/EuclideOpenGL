#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;

out vec3 vertexNormal;
out vec3 vertexColor;

void main() {

	vertexNormal= aNormal;

	vec4 positionWorld = vec4(aPos, 1.0);
	gl_Position = projection * (view * positionWorld);
	vertexColor = aColor;

}