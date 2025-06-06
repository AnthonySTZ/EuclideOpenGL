#pragma once

#include "Node.h"
#include "Fields/Float3Field.h"
#include "Fields/IntField.h"
#include "Fields/FloatField.h"

class Circle : public Node {

public:
	Circle() : Node("Circle") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Divisions"] = std::make_unique<IntField>("Divisions", 3, 3);
		parameters["Radius"] = std::make_unique<FloatField>("Radius", 1.0f, 0.0f);

		paramOrder.push_back("Divisions");
		paramOrder.push_back("Radius");
	}

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh createCircle(int divisions, float radius);
};