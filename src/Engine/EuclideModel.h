#pragma once

#include "Geometry.h"

#include <glad/glad.h>


class EuclideModel {

public:
	EuclideModel(Mesh& mesh) : mesh{ mesh } {};
	EuclideModel() = default;

	void drawFaces() const;
	//void drawEdges() const;
	//void drawVertices() const;
	void cleanup();
	void initBuffers();

	void update(Mesh& updatedMesh);


private:
	void updateBuffers();

	GLuint VAO = 0; 
	GLuint VBO = 0;
	GLuint elementbuffer = 0;

	Mesh mesh;
};