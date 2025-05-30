#include "Subdivide.h"

#include "../Utils.h"
#include <algorithm>

Mesh Subdivide::processOutput(uint32_t index)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();


    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    int subd = getParam<IntField>("Subdivisions")->getValue();

    return subdivide(inputMesh, subd);
}

Mesh Subdivide::subdivide(Mesh& mesh, int subdivisions)
{

    std::vector<Point> primPoints;

    for (uint32_t i = 0; i < mesh.primitives.size(); i++) {
        glm::vec3 centerPointOfPrim = mesh.getCenterOfPrimitive(i);
        primPoints.emplace_back(Point{ i,  centerPointOfPrim });
    }

    std::map<std::pair<uint32_t, uint32_t>, Point> edgePoints;
    uint32_t edgePointId = primPoints.size();
    for (auto& [uv, edge]: mesh.edges) {
        glm::vec3 avgEdges{ 0.0f };

        for (auto& primId: edge.primIds) // TODO: check if boundary
            avgEdges += mesh.getCenterOfPrimitive(primId);

        avgEdges += mesh.points[edge.u].position;
        avgEdges += mesh.points[edge.v].position;
        avgEdges /= 4.0f;
        edgePoints[uv] = Point{ edgePointId,  avgEdges };
        edgePointId++;
    }

    std::vector<Point> avgPoints;
    uint32_t avgPointsId = edgePointId;
    for (auto& point : mesh.points) {

        glm::vec3 avgConnectedPrimPoints{ 0.0f };
        for (auto& vertexId : point.vertices) {
            uint32_t primId = mesh.vertices[vertexId].primitiveId; // Connected prim
            avgConnectedPrimPoints += primPoints[primId].position;
        }
        avgConnectedPrimPoints /= static_cast<float>(point.vertices.size());

        glm::vec3 avgConnectedEdgePoints{ 0.0f };
        int nEdges = point.edges.size();
        for (auto& uv : point.edges) {
            glm::vec3 midPoint{ 0.0f };
            midPoint += mesh.points[mesh.edges[uv].u].position;
            midPoint += mesh.points[mesh.edges[uv].v].position;
            midPoint *= 0.5f;
            avgConnectedEdgePoints += midPoint;
        }
        avgConnectedEdgePoints /= static_cast<float>(nEdges);

        glm::vec3 barycentric = 
            (avgConnectedPrimPoints + avgConnectedEdgePoints * 2.0f + point.position * ((float)nEdges - 3.0f))
            / (float)nEdges;
        avgPoints.emplace_back(Point{ avgPointsId , barycentric });
        avgPointsId++;
    }


    Mesh::Builder subdBuilder;
    subdBuilder.points.insert(subdBuilder.points.end(), primPoints.begin(), primPoints.end());
    for (const auto& [_, pt] : edgePoints) subdBuilder.points.push_back(pt);
    subdBuilder.points.insert(subdBuilder.points.end(), avgPoints.begin(), avgPoints.end());

    for (uint32_t primId = 0; primId < mesh.primitives.size(); ++primId) {
        const auto& prim = mesh.primitives[primId];
        const Point& facePoint = primPoints[primId];

        size_t nVertices = prim.vertexIds.size();
        for (size_t i = 0; i < nVertices; ++i) {

            uint32_t firstPointCornerId = mesh.vertices[prim.vertexIds[(i - 1) % nVertices]].pointId;
            uint32_t secondPointCornerId = mesh.vertices[prim.vertexIds[i]].pointId;
            uint32_t thirdPointCornerId = mesh.vertices[prim.vertexIds[(i + 1) % nVertices]].pointId;
            auto edgeuv = std::minmax(firstPointCornerId, secondPointCornerId);
            auto edgevw = std::minmax(secondPointCornerId, thirdPointCornerId);
            const Point& edgeAvgPoint0 = edgePoints[edgeuv];
            const Point& edgeAvgPoint1 = edgePoints[edgevw];
            const Point& avgCornerPoint = avgPoints[secondPointCornerId];

            Face face{ {facePoint.id, edgeAvgPoint0.id, avgCornerPoint.id, edgeAvgPoint1.id} };
            subdBuilder.faces.push_back(face);
        }
    }

    return Mesh{ subdBuilder };

}
