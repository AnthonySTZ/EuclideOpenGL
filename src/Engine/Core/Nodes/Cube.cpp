#include "Cube.h"

#include "../Utils.h"

Mesh Cube::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

    Mesh::Builder cubeBuilder;

	glm::vec3 size = getParam<Float3Field>("Size")->toVec3();
	glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

	cubeBuilder.points = {
		// Front face (+X)
		{0, glm::vec3(0.5f, 0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, -0.5f}},
		{1, glm::vec3(0.5f, 0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, 0.5f}},
		{2, glm::vec3(0.5f, -0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, 0.5f}},
		{3, glm::vec3(0.5f, -0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, -0.5f}},

		//Back face (-X)
		{4, glm::vec3(-0.5f, 0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, -0.5f}},
		{5, glm::vec3(-0.5f, 0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, 0.5f, 0.5f}},
		{6, glm::vec3(-0.5f, -0.5f, -0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, 0.5f}},
		{7, glm::vec3(-0.5f, -0.5f, 0.5f) * size + translate, {1.0, 1.0, 1.0}, {0.5f, -0.5f, -0.5f}},
		
	};

	Face faceFront;
	faceFront.pointIds = { 0, 1, 2, 3 };
	Face faceBack;
	faceBack.pointIds = { 4, 5, 6, 7 };

	Face faceLeft; // (-Z)
	faceLeft.pointIds = { 5, 0, 3, 6 };

	Face faceRight;	// (+Z)
	faceRight.pointIds = { 1, 4, 7, 2 };

	Face faceTop;
	faceTop.pointIds = { 0, 5, 4, 1 };
	Face faceBottom;
	faceBottom.pointIds = { 3, 2, 7, 6 };


	cubeBuilder.faces = {
		faceFront, faceBack, faceLeft, faceRight, faceTop, faceBottom
	};

    return Mesh(cubeBuilder);
}
