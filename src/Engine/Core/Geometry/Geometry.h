#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>
#include <map>

struct Vertex;
struct Edge;
struct Face;

struct Halfedge {

	uint32_t twin = UINT32_MAX;
	uint32_t next = UINT32_MAX;
	uint32_t origin = UINT32_MAX;
	uint32_t edge = UINT32_MAX;
	uint32_t face = UINT32_MAX;

};

struct Edge {

	uint32_t halfedge = UINT32_MAX;
	uint32_t u = UINT32_MAX;
	uint32_t v = UINT32_MAX;

};

struct Face {

	uint32_t halfedge = UINT32_MAX;
	std::vector<uint32_t> vertexIndices;

};

struct Vertex {

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	uint32_t halfedge = UINT32_MAX;

};

struct BoundingBox {
	glm::vec3 min{ 0.0 };
	glm::vec3 max{ 0.0 };
};

class Mesh {

public:
	struct Builder {

		std::vector<Face> faces;
		std::vector<Vertex> vertices;

	};

	Mesh(const Mesh::Builder& builder) { updateMesh(builder); };
	Mesh() = default;
	void updateMesh(const Mesh::Builder& builder);
	void update() {
		recomputeMeshData(); triangulateFaces(); createWireframeIndices();
	};

	void recomputeMeshData();
	void triangulateFaces();
	void createWireframeIndices();
	glm::vec3 getCenterPos();
	BoundingBox getBoundingBox();

	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	std::vector<Face> faces;

	std::vector<Halfedge> halfedges;
	std::vector<uint32_t> triangulateIndices;
	std::vector<uint32_t> wireframeIndices;
	

};