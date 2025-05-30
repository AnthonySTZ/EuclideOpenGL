#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>
#include <map>

struct Attrib {
	uint32_t size = 1;
};

struct IntAttrib : public Attrib {
	uint32_t size = 1;
	int value = 0;
};

struct FloatAttrib : public Attrib {
	uint32_t size = 1;
	float value = 0.0f;
};

struct Float3Attrib : public Attrib {
	uint32_t size = 3;
	glm::vec3 value{ 0.0f };
};

struct Point {
	uint32_t id;
	glm::vec3 position{ 0.0, 0.0, 0.0 };
	glm::vec3 color{ 0.0, 0.0, 0.0 };
	glm::vec3 normal{ 0.0, 0.0, 0.0 };
	std::map<const char*, Attrib> attribs;
};

struct Vertex {
	uint32_t id;
	uint32_t pointId;
	uint32_t primitiveId;
};

struct Edge {
	uint32_t u;
	uint32_t v;
	std::vector<uint32_t> primIds;
};

struct Primitive {
	uint32_t id;
	std::vector<uint32_t> vertexIds;
};

struct Face {
	std::vector<uint32_t> pointIds;
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
	void updateHardNormalPoints();
	void update() {
		triangulateFaces();
		createWireframeIndices();
		updateHardNormalPoints();
		pointSize = points.size();
		primSize = primitives.size();
	};

	void addPrimitives(std::vector<Face> faces);
	void triangulateFaces();
	void createWireframeIndices();
	glm::vec3 getCenterPos();
	glm::vec3 getCenterOfPrimitive(uint32_t primId);
	Point& getPointFromVertexId(uint32_t vertexId) {
		return points[vertices[vertexId].pointId];
	};

	std::vector<Point> points;
	size_t pointSize = 0;
	std::vector<Vertex> vertices;
	std::map<std::pair<uint32_t, uint32_t>, Edge> edges;
	std::vector<Primitive> primitives;
	size_t primSize = 0;

	std::vector<uint32_t> triangulateIndices;
	std::vector<uint32_t> wireframeIndices;
	std::vector<Point> hardNormalPoints;
	

};