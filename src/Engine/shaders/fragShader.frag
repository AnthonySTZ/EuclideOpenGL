#version 330 core

in vec3 vertexNormal;
in vec3 vertexColor;

out vec4 outColor;

uniform vec3 lightDir = vec3(0.8f, -1.0f, 0.5f); // Better as a uniform

void main() {
    vec3 norm = normalize(vertexNormal);
    vec3 light = normalize(lightDir);

    vec3 ambient = vec3(0.3);

    float intensity = max(dot(light, norm), 0.0);
    vec3 diffuse = vertexColor * intensity * 0.5;

    vec3 result = ambient + diffuse;
    outColor = vec4(result, 1.0);
}