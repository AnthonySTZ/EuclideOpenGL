#include "Merge.h"

#include "../Utils.h"

Mesh Merge::processOutput(uint32_t index, bool *updateDirty) {

    auto it_0 = inputs.find(0);
    auto it_1 = inputs.find(1);
    if (it_0 == inputs.end() && it_1 == inputs.end()) {
        return Mesh();
    }
    if (it_0 == inputs.end()) {
        return it_1->second->getInputNode()->processOutput(it_1->second->getInputIndex());
    }
    if (it_1 == inputs.end()) {
        return it_0->second->getInputNode()->processOutput(it_0->second->getInputIndex());
    }

    bool isInput0Dirty = false;
    bool isInput1Dirty = false;
    Mesh inputMesh_0 = it_0->second->getInputNode()->processOutput(it_0->second->getInputIndex(), &isInput0Dirty);
    Mesh inputMesh_1 = it_1->second->getInputNode()->processOutput(it_1->second->getInputIndex(), &isInput1Dirty);

    if (!isDirty() && !isInput0Dirty && !isInput1Dirty){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	}

    Timer timer{ nodeName.c_str() };
    cachedMesh = mergeToMesh(inputMesh_0, inputMesh_1);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

Mesh Merge::mergeToMesh(Mesh& mesh_1, Mesh& mesh_2) {

    Mesh::Builder builder;
    builder.points.reserve(mesh_1.points.size() * mesh_2.points.size());
    builder.faces.reserve(mesh_1.primitives.size() + mesh_2.primitives.size());

    uint32_t pointOffset = (uint32_t)mesh_1.points.size();

    std::vector<Point> points = mesh_1.points;
    points.insert(points.end(), mesh_2.points.begin(), mesh_2.points.end());
    std::vector<Face> faces;

    for (auto& prim : mesh_1.primitives) {
        Face face;
        for (auto& vertIndex : prim.vertexIds) {
            face.pointIds.push_back(mesh_1.vertices[vertIndex].pointId);
        }
        faces.push_back(face);
    }

    for (auto& prim : mesh_2.primitives) {
        Face face;
        for (auto& vertIndex : prim.vertexIds) {
            face.pointIds.push_back(mesh_2.vertices[vertIndex].pointId + pointOffset);
        }
        faces.push_back(face);
    }

    builder.points.insert(builder.points.end(), points.begin(), points.end());
    builder.faces.insert(builder.faces.end(), faces.begin(), faces.end());

    return Mesh{ builder };

}