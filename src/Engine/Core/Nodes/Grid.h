#pragma once

#include "Node.h"

#include "Fields/Float3Field.h"
#include "Fields/IntField.h"
#include "Fields/FloatField.h"

class Grid : public Node {

public:
	Grid() : Node("Grid") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Rows"] = std::make_unique<IntField>("Rows", 1, 1);
		parameters["Columns"] = std::make_unique<IntField>("Columns", 1, 1);
		parameters["SizeX"] = std::make_unique<FloatField>("Size X", 10.0f, 0.0f);
		parameters["SizeZ"] = std::make_unique<FloatField>("Size Z", 10.0f, 0.0f);
		parameters["Translate"] = std::make_unique<Float3Field>("Translate");

		paramOrder.push_back("Rows");
		paramOrder.push_back("Columns");
		paramOrder.push_back("SizeX");
		paramOrder.push_back("SizeZ");
		paramOrder.push_back("Translate");
	};

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh createGrid(int rows, int cols, float sizeX, float sizeY, glm::vec3 translate = glm::vec3{0.0});
};