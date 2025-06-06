#include "CopyToPoints.h"

#include "../Utils.h"

Mesh CopyToPoints::processOutput(uint32_t index, bool *updateDirty) {

    auto it_0 = inputs.find(0);
    auto it_1 = inputs.find(1);
    if (it_0 == inputs.end() || it_1 == inputs.end()) {
        return Mesh();
    }


    Mesh inputMesh_0 = it_0->second->getInputNode()->processOutput(it_0->second->getInputIndex());
    Mesh inputMesh_1 = it_1->second->getInputNode()->processOutput(it_1->second->getInputIndex());

    return copyToPoints(inputMesh_0, inputMesh_1);
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
        }

        for (auto& prim : mesh_1.primitives) {
            Face face;
            for (auto& vertIndex : prim.vertexIds) {
                face.pointIds.push_back(mesh_1.vertices[vertIndex].pointId + pointOffset * (uint32_t)i);
            }
            faces.push_back(face);
        }

        builder.points.insert(builder.points.end(), points.begin(), points.end());
        builder.faces.insert(builder.faces.end(), faces.begin(), faces.end());

    }
    
    return Mesh{ builder };

}