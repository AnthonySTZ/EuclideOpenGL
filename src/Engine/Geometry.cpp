#include "Geometry.h"

#include <iostream>

struct TempHalfedge {
    TempHalfedge* twin = nullptr;
    TempHalfedge* next = nullptr;
    uint32_t origin = UINT32_MAX;
    uint32_t face = UINT32_MAX;
};

struct TempEdge {
    TempHalfedge* halfedge = nullptr;
    uint32_t u = UINT32_MAX;
    uint32_t v = UINT32_MAX;
};

void Mesh::recomputeMeshData()
{
    std::map<std::pair<uint32_t, uint32_t>, TempHalfedge*> halfedgesBuilder;
    std::map<std::pair<uint32_t, uint32_t>, TempEdge*> edgesBuilder;

    /* Creating Halfedges map */
    for (size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++) {

        Face face = faces[faceIndex];

        for (size_t i = 0; i < face.vertexIndices.size(); i++) {

            uint32_t u = face.vertexIndices[i];
            uint32_t v = face.vertexIndices[(i + 1) % face.vertexIndices.size()];

            halfedgesBuilder[{u, v}] = new TempHalfedge();
            halfedgesBuilder[{u, v}]->origin = u;
            halfedgesBuilder[{u, v}]->face = (uint32_t) faceIndex;

            if (edgesBuilder.find({ v, u }) == edgesBuilder.end()) { // Twin edge is not stored
                edgesBuilder[{u, v}] = new TempEdge();
                edgesBuilder[{u, v}]->halfedge = halfedgesBuilder[{u, v}];
                edgesBuilder[{u, v}]->u = u;
                edgesBuilder[{u, v}]->v = v;
            }

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
    halfedges.reserve(halfedgesBuilder.size());
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

    /* Flatten Edges to Vector */
    edges.clear();
    edges.reserve(edgesBuilder.size());
    for (auto& [key, tempEdge] : edgesBuilder) {
        uint32_t idx = pointerToIndex[tempEdge->halfedge];

        Edge edge;
        edge.halfedge = idx;
        edge.u = tempEdge->u;
        edge.v = tempEdge->v;
        edges.push_back(edge);
    }

}

void Mesh::triangulateFaces()
{

    for (auto const& face : faces) {

        if (face.vertexIndices.size() < 3)
            continue;

        for (size_t vertexIndex = 1; vertexIndex + 1 < face.vertexIndices.size() - 2; vertexIndex++) {

            uint32_t u = face.vertexIndices[0];
            uint32_t v = face.vertexIndices[vertexIndex + 1];
            uint32_t w = face.vertexIndices[vertexIndex + 2];

            triangulateIndices.push_back(u);
            triangulateIndices.push_back(v);
            triangulateIndices.push_back(w);

        }

    }

}

Mesh::Mesh(const Mesh::Builder& builder)
{
    vertices = builder.vertices;
    faces = builder.faces;
        
    recomputeMeshData(); // Compute halfedges and edges
    triangulateFaces(); // Compute the triangulate indices for rendering purpose

    for (auto& he : halfedges) {

        std::cout << "Pair : " << he.origin << " -> " << halfedges[he.next].origin << "\n";
    }

    std::cout << "Edges number : " << edges.size() << "\n";
}
