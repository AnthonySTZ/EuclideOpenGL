#include "HardenNormals.h"

Mesh HardenNormals::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    return hardenNormals(inputMesh);
}

Mesh HardenNormals::hardenNormals(Mesh mesh)
{

    for (auto& point: mesh.points){
        point.attribs.erase("Normal");
    }

    mesh.updateRenderVertices();

    return mesh;
}