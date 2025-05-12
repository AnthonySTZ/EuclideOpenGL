#include "Geometry.h"

std::map<std::pair<uint32_t, uint32_t>, Halfedge*> Geometry::initHalfedgesFromFaces(std::vector<Face> &faces)
{
    std::map<std::pair<uint32_t, uint32_t>, Halfedge*> halfedges;

    for (auto& face: faces) {

        for (size_t i = 0; i < face.vertexIndices.size(); i++) {

            uint32_t u = face.vertexIndices[i];
            uint32_t v = face.vertexIndices[(i + 1) % face.vertexIndices.size()];

            halfedges[{u, v}] = new Halfedge();
            halfedges[{u, v}]->face = &face;

        }

        for (size_t i = 0; i < face.vertexIndices.size(); i++) {

            uint32_t u = face.vertexIndices[i];
            uint32_t v = face.vertexIndices[(i + 1) % face.vertexIndices.size()];
            uint32_t w = face.vertexIndices[(i + 2) % face.vertexIndices.size()];

            halfedges[{u, v}]->next = halfedges[{v, w}];

            if (halfedges.find({ v, v }) != halfedges.end()) {
                halfedges[{u, v}]->twin = halfedges[{v, u}];
                halfedges[{v, u}]->twin = halfedges[{u, v}];
            }

        }

    }

    return halfedges;
}
