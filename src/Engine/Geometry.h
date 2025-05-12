#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

struct HalfEdge {

	HalfEdge* twin;
	HalfEdge* next;
	Vertex* vertex;
	Edge* edge;
	Face* face;

};

struct Edge {

	HalfEdge* halfEdge;
};

struct Face {

	HalfEdge* halfEdge;

};

struct Vertex {

	HalfEdge* halfEdge;

};
