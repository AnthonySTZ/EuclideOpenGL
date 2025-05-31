#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>

struct Attrib {
	virtual ~Attrib() = default;
	virtual std::unique_ptr<Attrib> clone() const = 0;
	uint32_t size = 1;
};

struct IntAttrib : public Attrib {
	uint32_t size = 1;
	int value = 0;

	IntAttrib(const int& v) : value(v) {}
	IntAttrib() = default;

	int getValue() { return value; }

	std::unique_ptr<Attrib> clone() const override {
        return std::make_unique<IntAttrib>(*this);
    }
};

struct FloatAttrib : public Attrib {
	float value = 0.0f;
	uint32_t size = 1;

	FloatAttrib(const float& v) : value(v) {}
	FloatAttrib() = default;

	float getValue() { return value; }

	std::unique_ptr<Attrib> clone() const override {
        return std::make_unique<FloatAttrib>(*this);
    }
};

struct Float3Attrib : public Attrib {
	glm::vec3 value{ 0.0f };
	uint32_t size = 3;

	Float3Attrib(const glm::vec3& v) : value(v) {}
	Float3Attrib() = default;

	glm::vec3 getValue() { return value; }

	std::unique_ptr<Attrib> clone() const override {
        return std::make_unique<Float3Attrib>(*this);
    }
};

struct RenderVertex {

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;

};

struct Point {
	uint32_t id;
	glm::vec3 position{ 0.0, 0.0, 0.0 };
	std::map<std::string, std::unique_ptr<Attrib>> attribs;
	std::vector<uint32_t> vertices;
	std::set<std::pair<uint32_t, uint32_t>> edges;

	template<typename T>
	T* getAttrib(const std::string& name, T* defaultValue) const {
		auto it = attribs.find(name);
		if (it == attribs.end()) return defaultValue;
		return dynamic_cast<T*>(it->second.get());
	}

	Point(uint32_t id, glm::vec3 pos) : id(id), position(pos) {}

	Point() = default;

    // Copy constructor
     Point(const Point& other) : id(other.id), position(other.position), vertices(other.vertices), edges(other.edges) {
        for (const auto& [key, value] : other.attribs) {
            attribs[key] = value->clone();
        }
    }

    Point& operator=(const Point& other) {
        if (this != &other) {
            id = other.id;
            position = other.position;
            vertices = other.vertices;
            edges = other.edges;
            attribs.clear();
            for (const auto& [key, value] : other.attribs) {
                attribs[key] = value->clone();
            }
        }
        return *this;
    }

    Point(Point&&) noexcept = default;
    Point& operator=(Point&&) noexcept = default;
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
	void updateRenderVertices();
	void update() {
		createWireframeIndices();
		updateRenderVertices();
		pointSize = points.size();
		primSize = primitives.size();
	};

	void addPrimitives(std::vector<Face> faces);
	void createWireframeIndices();
	RenderVertex pointToRenderVertex(Point& point, Float3Attrib& defaultColor, Float3Attrib& defaultNormal);
	glm::vec3 getCenterPos();
	glm::vec3 getCenterOfPrimitive(uint32_t primId);
	Point& getPointFromVertexId(uint32_t vertexId) {
		return points[vertices[vertexId].pointId];
	};
	std::vector<Edge> getBoundaryEdgesOfPoint(uint32_t pointId);

	std::vector<Point> points;
	size_t pointSize = 0;
	std::vector<Vertex> vertices;
	std::map<std::pair<uint32_t, uint32_t>, Edge> edges;
	std::vector<Primitive> primitives;
	size_t primSize = 0;

	std::vector<uint32_t> wireframeIndices;
	std::vector<RenderVertex> renderPoints;
	std::vector<RenderVertex> renderVertices;
	

};