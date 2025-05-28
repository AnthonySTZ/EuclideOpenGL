#include "Transform.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "../Utils.h"

Mesh Transform::processOutput(uint32_t index)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    Timer timer{ nodeName.c_str() };

    scaleMesh(inputMesh);
    rotateMesh(inputMesh);
    translateMesh(inputMesh);

    inputMesh.update();
    
    return inputMesh;
}

void Transform::translateMesh(Mesh& mesh) {
    glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

    for (auto& point : mesh.points) {
        point.position += translate;
    }

}

void Transform::scaleMesh(Mesh& mesh) {
    glm::vec3 scale = getParam<Float3Field>("Scale")->toVec3();

    for (auto& point : mesh.points) {
        point.position *= scale;
    }

}

void Transform::rotateMesh(Mesh& mesh) {
    glm::vec3 rotation = getParam<Float3Field>("Rotate")->toVec3();
    glm::vec3 xAxis{1.0, 0.0, 0.0};
    glm::vec3 yAxis{0.0, 1.0, 0.0};
    glm::vec3 zAxis{0.0, 0.0, 1.0};

    glm::mat4 rotMat{ 1.f };
    rotMat = glm::rotate(rotMat, glm::radians(rotation.x), xAxis);
    rotMat = glm::rotate(rotMat, glm::radians(rotation.y), yAxis);
    rotMat = glm::rotate(rotMat, glm::radians(rotation.z), zAxis);

    for (auto& point : mesh.points) {
        point.position = glm::vec3(rotMat * glm::vec4(point.position, 1.0));
    }

}

