#version 330 core

in vec3 vertexNormal;
in vec3 vertexColor;

out vec4 outColor;

uniform vec3 lightDir = vec3(0.8f, -1.0f, 0.5f);

void main() {
    vec3 norm = normalize(vertexNormal);
    vec3 light = normalize(lightDir);

    vec3 ambient = vec3(0.3);

    float intensity = (dot(light, norm) + 1) * 0.5;
    vec3 diffuse = vertexColor * intensity * .5;

    vec3 result = ambient + diffuse;
    outColor = vec4(result, 1.0);
}