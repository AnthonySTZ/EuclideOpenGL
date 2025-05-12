#pragma once

#include "Geometry.h"

#include <glad/glad.h>


class EuclideModel {

public:
	EuclideModel(Mesh& defaultMesh);
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
	GLuint faceIndicesBuffer = 0;
	GLuint EdgeIndicesBuffer = 0;

	Mesh mesh;
};