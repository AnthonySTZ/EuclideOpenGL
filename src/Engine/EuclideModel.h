#pragma once

#include "Geometry.h"

#include <glad/glad.h>


class EuclideModel {

public:
	struct Builder {
		std::vector<Vertex> vertices{};
		std::vector<uint32_t> indices{};
	};

	EuclideModel(const EuclideModel::Builder& builder);
	EuclideModel() = default;

	void draw() const;
	//void drawEdges() const;
	//void drawVertices() const;
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