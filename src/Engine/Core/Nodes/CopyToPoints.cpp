#include "CopyToPoints.h"

#include "../Utils.h"

Mesh& CopyToPoints::processOutput(uint32_t index, bool *updateDirty) {

    Timer timer{ nodeName.c_str() };

    auto it_0 = inputs.find(0);
    auto it_1 = inputs.find(1);
    if (it_0 == inputs.end() || it_1 == inputs.end()) {
        cachedMesh = Mesh();
        return cachedMesh;
    }

    bool isInput0Dirty = false;
    bool isInput1Dirty = false;
    Mesh inputMesh_0 = it_0->second->getInputNode()->processOutput(it_0->second->getInputIndex(), &isInput0Dirty);
    Mesh inputMesh_1 = it_1->second->getInputNode()->processOutput(it_1->second->getInputIndex(), &isInput1Dirty);

    if (!isDirty() && !isInput0Dirty && !isInput1Dirty){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    cachedMesh = copyToPoints(inputMesh_0, inputMesh_1);

    return cachedMesh;
}

Mesh CopyToPoints::copyToPoints(Mesh& mesh_1, Mesh& mesh_2) {
    
    Timer timer{ nodeName.c_str() };

    Mesh::Builder builder;
    builder.points.reserve(mesh_1.points.size() * mesh_2.points.size());
    builder.faces.reserve(mesh_1.primitives.size() * mesh_2.points.size());

    uint32_t pointOffset = (uint32_t)mesh_1.points.size();

    for (size_t i = 0; i < mesh_2.points.size(); i++) {

        std::vector<Point> points = mesh_1.points;
        std::vector<Face> faces;

        for (auto& point : points) {
            point.position += mesh_2.points[i].position;
            builder.addPoint(point.position);
        }

        std::vector<uint32_t> facePointIds;
        for (auto& prim : mesh_1.primitives) {
            facePointIds.clear();
            for (auto& vertIndex : prim.vertexIds) {
                facePointIds.push_back(mesh_1.vertices[vertIndex].pointId + pointOffset * (uint32_t)i);
            }
            builder.addFace(facePointIds);
        }

    }
    
    return Mesh{ builder };

}