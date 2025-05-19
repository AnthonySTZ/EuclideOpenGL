#include "Subdivide.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

Mesh Subdivide::processOutput(uint32_t index)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    int iterations = getParam<IntField>("Iterations")->getValue();
    subdivideMesh(inputMesh, iterations);

    return inputMesh;
}

void Subdivide::subdivideMesh(Mesh& mesh, int iterations) {
    
    

}