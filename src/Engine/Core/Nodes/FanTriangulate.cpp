#include "FanTriangulate.h"

#include "../Utils.h"
#include <algorithm>

Mesh& FanTriangulate::processOutput(uint32_t index, bool *updateDirty)
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

    cachedMesh = fanTriangulate(inputMesh);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

Mesh FanTriangulate::fanTriangulate(Mesh& mesh)
{

    Mesh::Builder builder;

    builder.points.reserve(mesh.points.size());
    for (auto& point: mesh.points){
        builder.addPoint(point.position);
    }

    uint32_t u, v, w;
    for (auto& prim : mesh.primitives) {

        size_t numVertex = prim.vertexIds.size();

        if (numVertex < 3)
            continue;

        for (size_t vertexIndex = 1; vertexIndex + 1 < numVertex; vertexIndex++) {

            u = mesh.vertices[prim.vertexIds[0]].pointId;
            v = mesh.vertices[prim.vertexIds[vertexIndex]].pointId;
            w = mesh.vertices[prim.vertexIds[vertexIndex + 1]].pointId;

            builder.addFace({u, v, w});

        }
    }

    return Mesh{builder};

}
