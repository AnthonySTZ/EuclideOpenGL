#version 330 core

in vec3 vertexColor;

out vec4 outColor;

void main() {
    vec2 coord = gl_PointCoord - vec2(0.5);
    if (dot(coord, coord) > 0.25) discard;

    outColor = vec4(vertexColor, 1.0);
}