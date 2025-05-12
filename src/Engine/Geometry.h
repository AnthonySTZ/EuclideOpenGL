#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};
