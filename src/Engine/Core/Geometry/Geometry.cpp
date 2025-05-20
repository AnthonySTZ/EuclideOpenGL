#include "Geometry.h"

#include <iostream>

#include "../Utils.h"

struct TempHalfedge {
    TempHalfedge* twin = nullptr;
    TempHalfedge* next = nullptr;
    TempHalfedge* prev = nullptr;
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

    {
        Timer timer{ "Halfedge creation" };

        /* Creating Halfedges map */
        for (size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++) {

            Face face = faces[faceIndex];
            size_t numVerts = face.vertexIndices.size();

            for (size_t i = 0; i < numVerts; i++) {

                uint32_t u = face.vertexIndices[i];
                uint32_t v = face.vertexIndices[(i + 1) % numVerts];

                auto uv = std::make_pair(u, v);
                auto vu = std::make_pair(v, u);

                TempHalfedge *he = new TempHalfedge();
                he->origin = u;
                he->face = (uint32_t)faceIndex;
                halfedgesBuilder[uv] = he;

                if (edgesBuilder.find(vu) == edgesBuilder.end()) { // Twin edge is not stored
                    TempEdge *edge = new TempEdge();
                    edge->halfedge = he;
                    edge->u = u;
                    edge->v = v;
                    edgesBuilder[uv] = edge;
                }

            }

            for (size_t i = 0; i < numVerts; i++) {

                uint32_t u = face.vertexIndices[i];
                uint32_t v = face.vertexIndices[(i + 1) % numVerts];
                uint32_t w = face.vertexIndices[(i + 2) % numVerts];

                auto uv = std::make_pair(u, v);
                auto vu = std::make_pair(v, u);
                auto vw = std::make_pair(v, w);

                halfedgesBuilder[uv]->next = halfedgesBuilder[vw];
                halfedgesBuilder[vw]->prev = halfedgesBuilder[uv];

                if (halfedgesBuilder.find(vu) != halfedgesBuilder.end()) {
                    halfedgesBuilder[uv]->twin = halfedgesBuilder[vu];
                    halfedgesBuilder[vu]->twin = halfedgesBuilder[uv];
                }

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
        if (tempHalfedge->prev)
            halfedges[idx].prev = pointerToIndex[tempHalfedge->prev];
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
    triangulateIndices.clear();
    for (auto const& face : faces) {

        if (face.vertexIndices.size() < 3)
            continue;

        for (size_t vertexIndex = 1; vertexIndex + 1 < face.vertexIndices.size(); vertexIndex++) {

            uint32_t u = face.vertexIndices[0];
            uint32_t v = face.vertexIndices[vertexIndex];
            uint32_t w = face.vertexIndices[vertexIndex + 1];

            triangulateIndices.push_back(u);
            triangulateIndices.push_back(v);
            triangulateIndices.push_back(w);

        }

    }

}

void Mesh::createWireframeIndices()
{

    wireframeIndices.clear();
    wireframeIndices.reserve(edges.size() * 2);
    for (const auto& edge : edges) {

        wireframeIndices.push_back(edge.u);
        wireframeIndices.push_back(edge.v);
    }

}

glm::vec3 Mesh::getCenterPos()
{
    BoundingBox boundingBox = getBoundingBox();
    glm::vec3 center = glm::vec3(
        (boundingBox.max.x + boundingBox.min.x) * 0.5f,
        (boundingBox.max.y + boundingBox.min.y) * 0.5f,
        (boundingBox.max.z + boundingBox.min.z) * 0.5f
        );
    return center;
}

BoundingBox Mesh::getBoundingBox() {
    BoundingBox bbox;
    if (vertices.size() == 0) return bbox;

    // Init bbox
    bbox.min = vertices[0].position;
    bbox.max = vertices[0].position;

    for (auto& vertex : vertices) {

        if (vertex.position.x < bbox.min.x) bbox.min.x = vertex.position.x;
        if (vertex.position.y < bbox.min.y) bbox.min.y = vertex.position.y;
        if (vertex.position.z < bbox.min.z) bbox.min.z = vertex.position.z;

        if (vertex.position.x > bbox.max.x) bbox.max.x = vertex.position.x;
        if (vertex.position.y > bbox.max.y) bbox.max.y = vertex.position.y;
        if (vertex.position.z > bbox.max.z) bbox.max.z = vertex.position.z;
    }

    return bbox;
}

void Mesh::updateMesh(const Mesh::Builder& builder)
{
    vertices = builder.vertices;
    faces = builder.faces;
        
    update();

    //std::cout << "Compute triangulation : " << triangulateIndices.size() << "\n";

    /*for (auto& he : halfedges) {

        std::cout << "Pair : " << he.origin << " -> " << halfedges[he.next].origin << "\n";
    }*/

    //std::cout << "Edges number : " << edges.size() << "\n";
}
