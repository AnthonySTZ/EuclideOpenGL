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
	EuclideModel() = default;

	void draw() const;
	void cleanup();
	void initBuffers();

	void update(const EuclideModel::Builder& builder);


private:
	void updateBuffers();

	GLuint VAO, VBO, elementbuffer;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};