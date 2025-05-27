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
	gridBuilder.points.reserve((rows + 1) * (cols + 1));
	gridBuilder.faces.reserve(rows * cols);

	float rowSpacing = sizeX / std::max(rows, 1);
	float colSpacing = sizeZ / std::max(cols, 1);

	float rowsOffset = rows * rowSpacing * 0.5f;
	float colsOffset = cols * colSpacing * 0.5f;

	uint32_t pointId = 0;
	for (int row = 0; row <= rows; row++) {
		for (int col = 0; col <= cols; col++) {
			float x = col * colSpacing - colsOffset;
			float z = row * rowSpacing - rowsOffset;
			
			glm::vec3 position = { x, 0.0, z };
			position += translate;
			glm::vec3 normal = { 0.0f, 1.0f, 0.0f };
			glm::vec3 color = { 0.0, 0.0, 0.0 };

			gridBuilder.points.push_back({ pointId, position, color, normal });
			pointId++;
		}
	}

	// Generate quad faces
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			uint32_t topLeft = row * (cols + 1) + col;
			uint32_t topRight = topLeft + 1;
			uint32_t bottomLeft = topLeft + (cols + 1);
			uint32_t bottomRight = bottomLeft + 1;

			Face quad;
			quad.pointIds = {
				topLeft,
				bottomLeft,
				bottomRight,
				topRight
			};
			gridBuilder.faces.push_back(quad);
		}
	}

	Timer timer{ "Mesh creation" };

	return Mesh{ gridBuilder };
}