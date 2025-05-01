#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <glad/glad.h>

#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
};

class EuclideModel {

public:
	struct Builder {
		std::vector<Vertex> vertices{};
		std::vector<uint32_t> indices{};
	};

	EuclideModel(const EuclideModel::Builder& builder);

	void draw() const;
	void initBuffers();

private:

	unsigned int VAO, VBO;
	GLuint elementbuffer;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};