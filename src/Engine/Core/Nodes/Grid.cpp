#include "Grid.h"

#include "../Utils.h"

Mesh Grid::processOutput(uint32_t index)
{	
	int rows = getParam<IntField>("Rows")->getValue();
	int cols = getParam<IntField>("Columns")->getValue();
	float sizeX = getParam<FloatField>("SizeX")->getValue();
	float sizeZ = getParam<FloatField>("SizeZ")->getValue();
	glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

	Timer timer{ nodeName.c_str() };
    return createGrid(rows, cols, sizeX, sizeZ, translate);
}

Mesh Grid::createGrid(int rows, int cols, float sizeX, float sizeZ, glm::vec3 translate) {

	Mesh::Builder gridBuilder;
	float rowSpacing = sizeX / std::max(rows, 1);
	float colSpacing = sizeZ / std::max(cols, 1);

	float rowsOffset = rows * rowSpacing * 0.5f;
	float colsOffset = cols * colSpacing * 0.5f;

	for (int row = 0; row <= rows; row++) {
		for (int col = 0; col <= cols; col++) {
			float x = col * colSpacing - colsOffset;
			float z = row * rowSpacing - rowsOffset;
			float y = 0.0f; // flat on XZ plane

			glm::vec3 position = { x, y, z };
			position += translate;
			glm::vec3 normal = { 0.0f, 1.0f, 0.0f };
			glm::vec3 color = { 0.8f, 0.8f, 0.8f };

			gridBuilder.vertices.push_back({ position, color, normal });
		}
	}

	// Generate quad faces
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			int topLeft = row * (cols + 1) + col;
			int topRight = topLeft + 1;
			int bottomLeft = topLeft + (cols + 1);
			int bottomRight = bottomLeft + 1;

			Face quad;
			quad.vertexIndices = {
				static_cast<uint32_t>(topLeft),
				static_cast<uint32_t>(bottomLeft),
				static_cast<uint32_t>(bottomRight),
				static_cast<uint32_t>(topRight)
			};
			gridBuilder.faces.push_back(quad);
		}
	}

	return Mesh{ gridBuilder };
}