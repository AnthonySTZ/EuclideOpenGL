#include "HardenNormals.h"

Mesh& HardenNormals::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()){
        cachedMesh = Mesh();
        return cachedMesh;
    }

    bool isInputDirty = false;
    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (!isDirty() && !isInputDirty){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	}

    cachedMesh = hardenNormals(inputMesh);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

Mesh HardenNormals::hardenNormals(Mesh mesh)
{

    for (auto& point: mesh.points){
        point.attribs.erase("Normal");
    }

    mesh.updateRenderVertices();

    return mesh;
}