#include "Transform.h"

Mesh Transform::processOutput(uint32_t index)
{
    auto it = inputs.find(index);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    translateMesh(inputMesh);
    // TODO: Add Scale and rotate
    return inputMesh;
}

void Transform::translateMesh(Mesh& mesh) {
    glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

    for (auto& vertex : mesh.vertices) {
        vertex.position += translate;
    }

}

// TODO: Add Scale and rotate
