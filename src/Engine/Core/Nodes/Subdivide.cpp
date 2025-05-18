#include "Subdivide.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

Mesh Subdivide::processOutput(uint32_t index)
{
    auto it = inputs.find(index);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    subdivideMesh(inputMesh);

    return inputMesh;
}

void Subdivide::subdivideMesh(Mesh& mesh) {
    


}