#include "EuclideModel.h"

#include <iostream>

EuclideModel::EuclideModel(Mesh& defaultMesh)
{

	mesh = defaultMesh;

}

void EuclideModel::drawFaces() const
{
	glBindVertexArray(vaoFaces);

	glDrawElements(
		GL_TRIANGLES,
		mesh.triangulateIndices.size(),
		GL_UNSIGNED_INT, 
		(void*)0
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
		mesh.vertices.size()
	);

	glBindVertexArray(0);
}

void EuclideModel::initBuffers()
{
	glGenVertexArrays(1, &vaoFaces);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &faceIndicesBuffer);

	glBindVertexArray(vaoFaces);

	// Bind and upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	// Bind and upload index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangulateIndices.size() * sizeof(uint32_t), mesh.triangulateIndices.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0);


	/* ------------ VAO WIREFRAME -------------- */
	glGenVertexArrays(1, &vaoWireframe);
	glBindVertexArray(vaoWireframe);

	glGenBuffers(1, &wireframeIndicesBuffer);

	// Bind and upload index data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wireframeIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.wireframeIndices.size() * sizeof(uint32_t), mesh.wireframeIndices.data(), GL_DYNAMIC_DRAW);

	// Unbind the VAO, VBO, AND INDEX BUFFER
	glBindVertexArray(0);


	/* ------------ VAO POINTS -------------- */
	glGenVertexArrays(1, &vaoPoints);
	glBindVertexArray(vaoPoints);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Bind and upload index data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// Unbind the VAO, VBO, AND INDEX BUFFER
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void EuclideModel::update() {

	std::cout << "Index count : " << mesh.triangulateIndices.size() << "\n";

	updateBuffers();

	std::cout << "Model updated!\n";

}

void EuclideModel::updateBuffers() {

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangulateIndices.size() * sizeof(unsigned int), mesh.triangulateIndices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wireframeIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.wireframeIndices.size() * sizeof(uint32_t), mesh.wireframeIndices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void EuclideModel::cleanup()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &faceIndicesBuffer);
	glDeleteVertexArrays(1, &vaoFaces);

	VBO = 0;
	faceIndicesBuffer = 0;
	vaoFaces = 0;
}
