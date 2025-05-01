#include "EuclideModel.h"

#include <iostream>

EuclideModel::EuclideModel(const EuclideModel::Builder& builder)
{

	vertices = builder.vertices;
	indices = builder.indices;
}

void EuclideModel::draw() const
{
	glBindVertexArray(VAO);

	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);

	glBindVertexArray(0);
}

void EuclideModel::initBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &elementbuffer);

	glBindVertexArray(VAO);

	// Bind and upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// Bind and upload index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	// Unbind the VAO
	glBindVertexArray(0);

	// Unbind the ARRAY BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
}

void EuclideModel::update(const EuclideModel::Builder &builder) {

	vertices = builder.vertices;
	indices = builder.indices;

	updateBuffers();

	std::cout << "Model updated!\n";

}

void EuclideModel::updateBuffers() {

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

}

void EuclideModel::cleanup()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteVertexArrays(1, &VAO);
}
