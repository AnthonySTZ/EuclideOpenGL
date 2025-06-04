#include "Duplicate.h"

#include "../Utils.h"
#include <algorithm>

#include "Transform.h"
#include "Merge.h"

Mesh Duplicate::processOutput(uint32_t index)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    int nCopies = getParam<IntField>("nCopies")->getValue();
    glm::vec3 rotation = getParam<Float3Field>("Rotate")->toVec3();
    glm::vec3 scale = getParam<Float3Field>("Scale")->toVec3();
    glm::vec3 translation = getParam<Float3Field>("Translate")->toVec3();

    if (nCopies < 1) return Mesh();

    Mesh outputMesh{inputMesh};

    for (int i=0; i<nCopies-1; i++){

        Transform::scaleMesh(inputMesh, scale);
        Transform::rotateMesh(inputMesh, rotation);
        Transform::translateMesh(inputMesh, translation);

        outputMesh = Merge::mergeToMesh(outputMesh, inputMesh);

    }

    return outputMesh;
}