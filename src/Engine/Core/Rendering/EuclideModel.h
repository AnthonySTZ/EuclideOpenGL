#pragma once

#include "../Geometry/Geometry.h"

#include <glad/glad.h>


class EuclideModel {

public:
	EuclideModel(Mesh defaultMesh);
	EuclideModel() {
		mesh = &defaultMesh;
	};

	void drawFaces() const;
	void drawWireframe() const;
	void drawPoints() const;
	void cleanup();
	void initBuffers();

	void update();
	void updateMesh(Mesh& newMesh) { 
		mesh = &newMesh;
		update();
	}
	Mesh* getMesh() { return mesh; };

	size_t pointCount() const { return mesh->pointSize; };
	size_t primitiveCount() const { return mesh->primSize; };


private:
	void updateBuffers();

	GLuint vaoFaces = 0; 
	GLuint vaoWireframe = 0;
	GLuint vaoPoints = 0;
	GLuint VBOVertices = 0;
	GLuint VBOPoints = 0;
	GLuint faceIndicesBuffer = 0;
	GLuint wireframeIndicesBuffer = 0;

	Mesh defaultMesh;
	Mesh* mesh;
};