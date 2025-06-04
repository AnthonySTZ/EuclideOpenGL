#pragma once

#include "Node.h"
#include "Fields/IntField.h"
#include "Fields/FloatField.h"

class Sphere : public Node {

public:
	Sphere() : Node("Sphere") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Rows"] = std::make_unique<IntField>("Rows", 8, 0);
		parameters["Columns"] = std::make_unique<IntField>("Columns", 16, 0);
		parameters["Radius"] = std::make_unique<FloatField>("Radius", 1.0f, 0.0f);

		paramOrder.push_back("Rows");
		paramOrder.push_back("Columns");
		paramOrder.push_back("Radius");
	}

	Mesh processOutput(uint32_t index) override;
	static Mesh createSphere(int rows, int columns, float radius);
};