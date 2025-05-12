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

	Halfedge* twin;
	Halfedge* next;
	Vertex* vertex;
	Edge* edge;
	Face* face;

};

struct Edge {

	Halfedge* halfedge;
	uint32_t u;
	uint32_t v;

};

struct Face {

	Halfedge* halfedge;
	std::vector<uint32_t> vertexIndices;

};

struct Vertex {

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	//Halfedge* halfedge;

};

class Geometry {

public:

	static std::map<std::pair<uint32_t, uint32_t>, Halfedge*> initHalfedgesFromFaces(std::vector<Face> &faces);

};