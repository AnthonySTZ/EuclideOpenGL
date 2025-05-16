#include "Transform.h"

Mesh Transform::processOutput(uint32_t index)
{
    auto it = inputs.find(index);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    scaleMesh(inputMesh);
    translateMesh(inputMesh);
    // TODO: Add rotate
    return inputMesh;
}

void Transform::translateMesh(Mesh& mesh) {
    glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

    for (auto& vertex : mesh.vertices) {
        vertex.position += translate;
    }

}

void Transform::scaleMesh(Mesh& mesh) {
    glm::vec3 scale = getParam<Float3Field>("Scale")->toVec3();

    for (auto& vertex : mesh.vertices) {
        vertex.position *= scale;
    }

}

// TODO: Add rotate
