#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 vertexColor;

void main() {
	
	vec4 positionWorld = vec4(aPos, 1.0);
	vec4 camPos = vec4(inverse(view)[3]);
	positionWorld = positionWorld + normalize(camPos - positionWorld) * 0.01;
	gl_Position = projection * (view * positionWorld);
	gl_PointSize = 8.0;
	vertexColor = vec3(0.0, 0.0, 1.0);

}