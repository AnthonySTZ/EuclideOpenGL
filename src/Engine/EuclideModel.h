#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <glad/glad.h>

#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
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
	void drawWireframe() const;
	void cleanup();
	void initBuffers();

	void update(const EuclideModel::Builder& builder);


private:
	void updateBuffers();

	GLuint VAO = 0; 
	GLuint VBO = 0;
	GLuint elementbuffer = 0;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};