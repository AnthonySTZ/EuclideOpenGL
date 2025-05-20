#include "CopyToPoints.h"

#include "../Utils.h"

Mesh CopyToPoints::processOutput(uint32_t index) {

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
    
    Timer timer{ "copyToPoints" };

    Mesh::Builder builder;
    builder.vertices.reserve(mesh_1.vertices.size() * mesh_2.vertices.size());
    builder.vertices.reserve(mesh_1.faces.size() * mesh_2.vertices.size());

    uint32_t vertOffset = mesh_1.vertices.size();

    for (size_t i = 0; i < mesh_2.vertices.size(); i++) {

        std::vector<Vertex> vertices = mesh_1.vertices;
        std::vector<Face> faces = mesh_1.faces;

        for (auto& vertex : vertices) {
            vertex.position += mesh_2.vertices[i].position;
        }

        for (auto& face : faces) {
            for (auto& vertIndex : face.vertexIndices) {
                vertIndex += vertOffset * i;
            }
        }

        builder.vertices.insert(builder.vertices.end(), vertices.begin(), vertices.end());
        builder.faces.insert(builder.faces.end(), faces.begin(), faces.end());

    }

    return Mesh{ builder };

}