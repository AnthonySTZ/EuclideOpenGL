#include "Geometry.h"

#include <iostream>

#include "../Utils.h"
#include "../Nodes/BoundingBox.h"
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
            vertices.emplace_back(Vertex{
                vertexId, 
                pointId,
                primId 
            });
            prim.vertexIds.push_back(vertexId);

            auto& point = points[pointId]; 
            point.vertices.push_back(vertexId);
            
            uint32_t next_pointId = face.pointIds[(i + 1) % numVertices];

            auto [u, v] = std::minmax(pointId, next_pointId);
            auto edgeKey = std::make_pair(u, v);
            auto [it, inserted] = edges.try_emplace(edgeKey, Edge{ pointId, next_pointId, {primId} });
            if (!inserted) {
                it->second.primIds.push_back(primId);
            }
            
            point.edges.insert(edgeKey);
            points[next_pointId].edges.insert(edgeKey);
            
            vertexId++;
        }

        primitives.push_back(std::move(prim));
        primId++;
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
    BoundingBox::BBox boundingBox = BoundingBox::computeBoundingBox(*this);
    glm::vec3 center = glm::vec3(
        (boundingBox.max.x + boundingBox.min.x) * 0.5f,
        (boundingBox.max.y + boundingBox.min.y) * 0.5f,
        (boundingBox.max.z + boundingBox.min.z) * 0.5f
        );
    return center;
}

glm::vec3 Mesh::getCenterOfPrimitive(uint32_t primId)
{
    glm::vec3 avgPrim{ 0.0f };
    if (primitives[primId].vertexIds.size() < 1) return avgPrim;

    for (auto& vertexId : primitives[primId].vertexIds) {
        avgPrim += getPointFromVertexId(vertexId).position;
    }

    return avgPrim / static_cast<float>(primitives[primId].vertexIds.size());
}

std::vector<Edge> Mesh::getBoundaryEdgesOfPoint(uint32_t pointId)
{
    std::vector<Edge> boundaryEdges;

    for (auto& edgeuv : points[pointId].edges) {

        if (edges[edgeuv].primIds.size() < 2) {
            boundaryEdges.push_back(edges[edgeuv]);
        }

    }

    return boundaryEdges;
}

void Mesh::updateMesh(const Mesh::Builder& builder)
{
    points = builder.points;
    
    primitives.clear();
    edges.clear();
    vertices.clear();

    addPrimitives(builder.faces);

    update();
}

void Mesh::updateRenderVertices()
{
    Float3Attrib wireframeColor{ {.1f, .1f, .1f} };
    Float3Attrib defaultColor{ {.9f, .9f, .9f} };
    Float3Attrib noNormal{{0.0f, 0.0f, 0.0f}};

    renderPoints.clear();
    renderPoints.reserve(points.size());
    for (auto& point: points){
        RenderVertex v = pointToRenderVertex(point, wireframeColor, noNormal);
        renderPoints.push_back(v);
    }

    renderVertices.clear();
    renderVertices.reserve(vertices.size());

    for (auto& prim : primitives) {

        size_t numVertex = prim.vertexIds.size();

        if (numVertex < 3)
            continue;

        uint32_t u = vertices[prim.vertexIds[0]].pointId;
        uint32_t v = vertices[prim.vertexIds[1]].pointId;
        uint32_t w = vertices[prim.vertexIds[2]].pointId;
        glm::vec3 edge1 = points[v].position - points[u].position;
        glm::vec3 edge2 = points[w].position - points[u].position;
        glm::vec3 normal = glm::cross(edge1, edge2);
        Float3Attrib normalField { normal };

        for (size_t vertexIndex = 1; vertexIndex + 1 < numVertex; vertexIndex++) {

            u = vertices[prim.vertexIds[0]].pointId;
            v = vertices[prim.vertexIds[vertexIndex]].pointId;
            w = vertices[prim.vertexIds[vertexIndex + 1]].pointId;

            RenderVertex pu = pointToRenderVertex(points[u], defaultColor, normalField);            
            RenderVertex pv = pointToRenderVertex(points[v], defaultColor, normalField);
            RenderVertex pw = pointToRenderVertex(points[w], defaultColor, normalField);

            renderVertices.push_back(pu);
            renderVertices.push_back(pv);
            renderVertices.push_back(pw);

        }

        for (auto& vertexId: prim.vertexIds){
            vertices[vertexId].normal = normal;
        }

    }


}

RenderVertex Mesh::pointToRenderVertex(Point& point, Float3Attrib& defaultColor, Float3Attrib& defaultNormal){
    RenderVertex vertex;
    vertex.position = point.position;
    vertex.color = point.getAttrib<Float3Attrib>("Color", &defaultColor)->getValue();
    vertex.normal = point.getAttrib<Float3Attrib>("Normal", &defaultNormal)->getValue();

    return vertex;
}
