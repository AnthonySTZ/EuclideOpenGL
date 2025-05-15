#include "Cube.h"

Mesh Cube::processOutput(uint32_t index)
{
    Mesh::Builder cubeBuilder;

	glm::vec3 size = getParam<Float3Field>("Size")->toVec3();
	glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

	cubeBuilder.vertices = {
		// Front face (+X)
		{glm::vec3(0.5f, 0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, -0.5f}},
		{glm::vec3(0.5f, 0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, 0.5f}},
		{glm::vec3(0.5f, -0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, 0.5f}},
		{glm::vec3(0.5f, -0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, -0.5f}},

		//Back face (-X)
		{glm::vec3(-0.5f, 0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, -0.5f}},
		{glm::vec3(-0.5f, 0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, 0.5f}},
		{glm::vec3(-0.5f, -0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, 0.5f}},
		{glm::vec3(-0.5f, -0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, -0.5f}},
		
	};

	Face faceFront;
	faceFront.vertexIndices = { 0, 1, 2, 3 };
	Face faceBack;
	faceBack.vertexIndices = { 4, 5, 6, 7 };

	Face faceLeft; // (-Z)
	faceLeft.vertexIndices = { 5, 0, 3, 6 };

	Face faceRight;	// (+Z)
	faceRight.vertexIndices = { 1, 4, 7, 2 };

	Face faceTop;
	faceTop.vertexIndices = { 0, 5, 4, 1 };
	Face faceBottom;
	faceBottom.vertexIndices = { 3, 2, 7, 6 };


	cubeBuilder.faces = {
		faceFront, faceBack, faceLeft, faceRight, faceTop, faceBottom
	};

    return Mesh(cubeBuilder);
}
