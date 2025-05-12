#include "Geometry.h"

#include <iostream>

struct TempHalfedge {
    TempHalfedge* twin = nullptr;
    TempHalfedge* next = nullptr;
    uint32_t origin = UINT32_MAX;
    uint32_t face = UINT32_MAX;
};

void Mesh::recomputeMeshData()
{
    std::map<std::pair<uint32_t, uint32_t>, TempHalfedge*> halfedgesBuilder;

    /* Creating Halfedges map */
    for (size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++) {

        Face face = faces[faceIndex];

        for (size_t i = 0; i < face.vertexIndices.size(); i++) {

            uint32_t u = face.vertexIndices[i];
            uint32_t v = face.vertexIndices[(i + 1) % face.vertexIndices.size()];

            halfedgesBuilder[{u, v}] = new TempHalfedge();
            halfedgesBuilder[{u, v}]->origin = u;
            halfedgesBuilder[{u, v}]->face = (uint32_t) faceIndex;

        }

        for (size_t i = 0; i < face.vertexIndices.size(); i++) {

            uint32_t u = face.vertexIndices[i];
            uint32_t v = face.vertexIndices[(i + 1) % face.vertexIndices.size()];
            uint32_t w = face.vertexIndices[(i + 2) % face.vertexIndices.size()];

            halfedgesBuilder[{u, v}]->next = halfedgesBuilder[{v, w}];

            if (halfedgesBuilder.find({ v, u }) != halfedgesBuilder.end()) {
                halfedgesBuilder[{u, v}]->twin = halfedgesBuilder[{v, u}];
                halfedgesBuilder[{v, u}]->twin = halfedgesBuilder[{u, v}];
            }

        }
    }

    /* Flatten Halfedges to Vector */
    halfedges.clear();
    std::map<TempHalfedge*, uint32_t> pointerToIndex;

    for (auto& [key, tempHalfedge] : halfedgesBuilder) {

        uint32_t idx = (uint32_t)halfedges.size();
        pointerToIndex[tempHalfedge] = idx;

        Halfedge halfedge;
        halfedge.origin = tempHalfedge->origin;
        halfedge.face = tempHalfedge->face;
        halfedges.push_back(halfedge);

    }

    for (auto& [key, tempHalfedge] : halfedgesBuilder) {
        uint32_t idx = pointerToIndex[tempHalfedge];

        if (tempHalfedge->twin)
            halfedges[idx].twin = pointerToIndex[tempHalfedge->twin];
        if (tempHalfedge->next)
            halfedges[idx].next = pointerToIndex[tempHalfedge->next];
    }

}

Mesh::Mesh(const Mesh::Builder& builder)
{
    vertices = builder.vertices;
    faces = builder.faces;
        
    recomputeMeshData();

    for (auto& he : halfedges) {

        std::cout << "Pair : " << he.origin << " -> " << halfedges[he.next].origin << "\n";
    }
}
