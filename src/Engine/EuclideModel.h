#pragma once

#include "Core/Geometry.h"

#include <glad/glad.h>


class EuclideModel {

public:
	EuclideModel(Mesh& defaultMesh);
	EuclideModel() = default;

	void drawFaces() const;
	void drawWireframe() const;
	void drawPoints() const;
	void cleanup();
	void initBuffers();

	void update(Mesh::Builder& meshBuilder);


private:
	void updateBuffers();

	GLuint vaoFaces = 0; 
	GLuint vaoWireframe = 0;
	GLuint vaoPoints = 0;
	GLuint VBO = 0;
	GLuint faceIndicesBuffer = 0;
	GLuint wireframeIndicesBuffer = 0;

	Mesh mesh;
};