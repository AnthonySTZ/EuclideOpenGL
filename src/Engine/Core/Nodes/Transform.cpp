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
    Timer timer{"translate"};
    glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();
    
    for (auto& point : mesh.points) {
        point.position += translate;
    }
    
}

void Transform::scaleMesh(Mesh& mesh) {
    Timer timer{"scale"};
    glm::vec3 scale = getParam<Float3Field>("Scale")->toVec3();
    
    for (auto& point : mesh.points) {
        point.position *= scale;
    }
    
}

void Transform::rotateMesh(Mesh& mesh) {
    Timer timer{"rotate"};
    glm::vec3 rotation = getParam<Float3Field>("Rotate")->toVec3();
    glm::vec3 xAxis{1.0, 0.0, 0.0};
    glm::vec3 yAxis{0.0, 1.0, 0.0};
    glm::vec3 zAxis{0.0, 0.0, 1.0};

    glm::vec3 radians = glm::radians(rotation);
    glm::mat4 rotMat{ 1.f };
    rotMat = glm::rotate(rotMat, radians.x, xAxis);
    rotMat = glm::rotate(rotMat, radians.y, yAxis);
    rotMat = glm::rotate(rotMat, radians.z, zAxis);

    for (auto& point : mesh.points) {
        point.position = glm::vec3(rotMat * glm::vec4(point.position, 1.0));
    }

}

