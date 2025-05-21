#include "Geometry.h"

#include <iostream>

#include "../Utils.h"
#include <algorithm>

void Mesh::addPrimitives(std::vector<Face> faces)
{
    Timer timer{ "addPrimitives" };

    uint32_t primId = primitives.size();
    primitives.reserve(primitives.size() + faces.size());

    uint32_t vertexId = vertices.size();
    uint32_t verticesToAdd = 0;
    for (const auto& face : faces) {
        verticesToAdd += face.pointIds.size();
    }

    vertices.reserve(vertices.size() + verticesToAdd);

    for (const auto& face : faces) {
        Primitive prim;
        prim.id = primId;

        uint32_t numVertices = face.pointIds.size();
        prim.vertexIds.reserve(numVertices);

        for (size_t i = 0; i < numVertices; i++) {

            uint32_t pointId = face.pointIds[i];
            Vertex vertex{};
            vertex.id = vertexId;
            vertex.pointId = pointId;
            vertex.primitiveId = primId;
            vertices.push_back(vertex);
            prim.vertexIds.push_back(vertexId);
            vertexId++;

            uint32_t next_pointId = face.pointIds[(i + 1) % numVertices];
            auto [u, v] = std::minmax(pointId, next_pointId);
            edges.try_emplace({u, v}, Edge{ pointId , next_pointId });

        }

        primitives.push_back(std::move(prim));
        primId++;
    }

}

void Mesh::triangulateFaces()
{
    Timer timer{ "triangulateFaces" };

    triangulateIndices.clear();
    for (auto const& prim : primitives) {

        size_t numVertex = prim.vertexIds.size();

        if (numVertex < 3)
            continue;

        for (size_t vertexIndex = 1; vertexIndex + 1 < numVertex; vertexIndex++) {

            uint32_t u = vertices[prim.vertexIds[0]].pointId;
            uint32_t v = vertices[prim.vertexIds[vertexIndex]].pointId;
            uint32_t w = vertices[prim.vertexIds[vertexIndex + 1]].pointId;

            triangulateIndices.push_back(u);
            triangulateIndices.push_back(v);
            triangulateIndices.push_back(w);

        }

    }

}

void Mesh::createWireframeIndices()
{
    Timer timer{ "createWireframeIndices" };

    wireframeIndices.clear();
    wireframeIndices.reserve(edges.size() * 2);
    for (const auto& [key, edge] : edges) {

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
    if (points.size() == 0) return bbox;

    // Init bbox
    bbox.min = points[0].position;
    bbox.max = points[0].position;

    for (auto& point : points) {

        if (point.position.x < bbox.min.x) bbox.min.x = point.position.x;
        if (point.position.y < bbox.min.y) bbox.min.y = point.position.y;
        if (point.position.z < bbox.min.z) bbox.min.z = point.position.z;

        if (point.position.x > bbox.max.x) bbox.max.x = point.position.x;
        if (point.position.y > bbox.max.y) bbox.max.y = point.position.y;
        if (point.position.z > bbox.max.z) bbox.max.z = point.position.z;
    }

    return bbox;
}

void Mesh::updateMesh(const Mesh::Builder& builder)
{
    points = builder.points;
    
    primitives.clear();
    edges.clear();
    vertices.clear();

    addPrimitives(builder.faces);

    update();

    //std::cout << "Compute triangulation : " << triangulateIndices.size() << "\n";

    /*for (auto& he : halfedges) {

        std::cout << "Pair : " << he.origin << " -> " << halfedges[he.next].origin << "\n";
    }*/

    //std::cout << "Edges number : " << edges.size() << "\n";
}
