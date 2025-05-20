#include "Merge.h"

#include "../Utils.h"

Mesh Merge::processOutput(uint32_t index) {

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


    Mesh inputMesh_0 = it_0->second->getInputNode()->processOutput(it_0->second->getInputIndex());
    Mesh inputMesh_1 = it_1->second->getInputNode()->processOutput(it_1->second->getInputIndex());

    mergeToMesh(inputMesh_0, inputMesh_1);

    return inputMesh_0;
}

void Merge::mergeToMesh(Mesh& mesh1, Mesh& mesh2) {

    Timer timer{ nodeName.c_str() };

    /*size_t vertexOffset = mesh1.vertices.size();

    mesh1.vertices.insert(mesh1.vertices.end(), mesh2.vertices.begin(), mesh2.vertices.end());
    for (auto& face : mesh2.faces) {
        for (auto& vertex : face.vertexIndices) {
            vertex += vertexOffset;
        }
    }
    mesh1.faces.insert(mesh1.faces.end(), mesh2.faces.begin(), mesh2.faces.end());*/

    mesh1.update();

}