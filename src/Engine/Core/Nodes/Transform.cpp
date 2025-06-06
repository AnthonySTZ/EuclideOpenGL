#include "Transform.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "../Utils.h"

Mesh Transform::processOutput(uint32_t index, bool *updateDirty)
{
    Timer timer{ nodeName.c_str() };
    
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();    
    
    bool isInputDirty = false;
    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (!isInputDirty && !isDirty()){
        if (updateDirty != nullptr) *updateDirty = false;
        return cachedMesh;
    } 
    
    glm::vec3 rotation = getParam<Float3Field>("Rotate")->toVec3();
    glm::vec3 scale = getParam<Float3Field>("Scale")->toVec3();
    glm::vec3 translation = getParam<Float3Field>("Translate")->toVec3();

    cachedMesh = scaleMesh(inputMesh, scale);
    cachedMesh = rotateMesh(cachedMesh, rotation);
    cachedMesh = translateMesh(cachedMesh, translation);
    
    if (updateDirty != nullptr) *updateDirty = true;
    dirty = false;

    return cachedMesh;
}

bool isVec3Null(glm::vec3 vec) {
    return (vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f);
}

Mesh Transform::translateMesh(Mesh &mesh, glm::vec3 translation) {
    Timer timer{"translate"};
    
    if (isVec3Null(translation)) return mesh;
    
    for (auto& point : mesh.points) {
        point.position += translation;
    }
    
    return mesh;
}

Mesh Transform::scaleMesh(Mesh &mesh, glm::vec3 scale) {
    Timer timer{"scale"};
    
    if (isVec3Null(scale)) return mesh;

    for (auto& point : mesh.points) {
        point.position *= scale;
    }
    
    return mesh;
}

Mesh Transform::rotateMesh(Mesh &mesh, glm::vec3 rotation) {
    Timer timer{"rotate"};

    if (isVec3Null(rotation)) return mesh;
    
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

    return mesh;

}

