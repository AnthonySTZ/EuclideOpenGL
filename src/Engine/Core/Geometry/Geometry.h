#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>
#include <map>

struct Point {
	uint32_t id;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};

struct Vertex {
	uint32_t id;
	uint32_t pointId;
	uint32_t primitiveId;
};

struct Edge {
	uint32_t u;
	uint32_t v;
};

struct Primitive {
	uint32_t id;
	std::vector<uint32_t> vertexIds;
};

struct Face {
	std::vector<uint32_t> pointIds;
};



struct BoundingBox {
	glm::vec3 min{ 0.0 };
	glm::vec3 max{ 0.0 };
};

class Mesh {

public:
	struct Builder {

		std::vector<Face> faces;
		std::vector<Point> points;

	};

	Mesh(const Mesh::Builder& builder) { updateMesh(builder); };
	Mesh() = default;
	void updateMesh(const Mesh::Builder& builder);
	void update() {
		triangulateFaces();
		createWireframeIndices();
		pointSize = points.size();
		primSize = primitives.size();
	};

	void addPrimitives(std::vector<Face> faces);
	void triangulateFaces();
	void createWireframeIndices();
	glm::vec3 getCenterPos();
	BoundingBox getBoundingBox();

	std::vector<Point> points;
	size_t pointSize = 0;
	std::vector<Vertex> vertices;
	std::map<std::pair<uint32_t, uint32_t>, Edge> edges;
	std::vector<Primitive> primitives;
	size_t primSize = 0;

	std::vector<uint32_t> triangulateIndices;
	std::vector<uint32_t> wireframeIndices;
	

};