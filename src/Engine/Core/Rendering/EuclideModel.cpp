#include "EuclideModel.h"

#include <iostream>

EuclideModel::EuclideModel(Mesh& defaultMesh)
{

	mesh = defaultMesh;

}

void EuclideModel::drawFaces() const
{
	glBindVertexArray(vaoFaces);

	glDrawArrays(
		GL_TRIANGLES,
		0,
		mesh.hardNormalPoints.size()
	);

	glBindVertexArray(0);
}

void EuclideModel::drawWireframe() const
{
	glBindVertexArray(vaoWireframe);

	glDrawElements(
		GL_LINES,
		mesh.wireframeIndices.size(),
		GL_UNSIGNED_INT,
		(void*)0
	);

	glBindVertexArray(0);
}

void EuclideModel::drawPoints() const
{
	glBindVertexArray(vaoPoints);

	glDrawArrays(
		GL_POINTS, 
		0,
		mesh.points.size()
	);

	glBindVertexArray(0);
}

void EuclideModel::initBuffers()
{
	glGenVertexArrays(1, &vaoFaces);
	glGenBuffers(1, &VBOVertices);
	glGenBuffers(1, &faceIndicesBuffer);

	glBindVertexArray(vaoFaces);

	// Bind and upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBOVertices);
	glBufferData(GL_ARRAY_BUFFER, mesh.hardNormalPoints.size() * sizeof(Point), mesh.hardNormalPoints.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, color));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, normal));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);


	/* ------------ VAO WIREFRAME -------------- */
	glGenVertexArrays(1, &vaoWireframe);
	glGenBuffers(1, &VBOPoints);
	glBindVertexArray(vaoWireframe);

	glGenBuffers(1, &wireframeIndicesBuffer);

	// Bind and upload index data
	glBindBuffer(GL_ARRAY_BUFFER, VBOPoints);
	glBufferData(GL_ARRAY_BUFFER, mesh.points.size() * sizeof(Point), mesh.points.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, color));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wireframeIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.wireframeIndices.size() * sizeof(uint32_t), mesh.wireframeIndices.data(), GL_DYNAMIC_DRAW);

	// Unbind the VAO, VBOVertices, AND INDEX BUFFER
	glBindVertexArray(0);

	/* ------------ VAO POINTS -------------- */
	glGenVertexArrays(1, &vaoPoints);
	glBindVertexArray(vaoPoints);
	glBindBuffer(GL_ARRAY_BUFFER, VBOPoints);

	// Bind and upload index data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, position));
	glEnableVertexAttribArray(0);

	// Unbind the VAO, VBOVertices, AND INDEX BUFFER
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void EuclideModel::update() {
	updateBuffers();
}

void EuclideModel::updateBuffers() {

	glBindBuffer(GL_ARRAY_BUFFER, VBOVertices);
	glBufferData(GL_ARRAY_BUFFER, mesh.hardNormalPoints.size() * sizeof(Point), mesh.hardNormalPoints.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPoints);
	glBufferData(GL_ARRAY_BUFFER, mesh.points.size() * sizeof(Point), mesh.points.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wireframeIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.wireframeIndices.size() * sizeof(uint32_t), mesh.wireframeIndices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void EuclideModel::cleanup()
{
	glDeleteBuffers(1, &VBOVertices);
	glDeleteBuffers(1, &VBOPoints);
	glDeleteBuffers(1, &faceIndicesBuffer);
	glDeleteVertexArrays(1, &vaoFaces);

	VBOVertices = 0;
	VBOPoints = 0;
	faceIndicesBuffer = 0;
	vaoFaces = 0;
}
