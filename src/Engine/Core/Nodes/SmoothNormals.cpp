#include "SmoothNormals.h"

Mesh SmoothNormals::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();

    bool isInputDirty = false;
    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (!isDirty() && !isInputDirty){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    cachedMesh = smoothNormals(inputMesh);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

Mesh SmoothNormals::smoothNormals(Mesh mesh)
{

    for (auto& point: mesh.points){

        uint32_t nVertex = point.vertices.size();
        if (nVertex == 0) continue;

        glm::vec3 normal{0.0f};

        for (auto& vertexId: point.vertices){

            normal += mesh.vertices[vertexId].normal;

        }

        normal /= nVertex;
        point.attribs["Normal"] = std::make_unique<Float3Attrib>(glm::normalize(normal));
    }

    mesh.updateRenderVertices();

    return mesh;
}