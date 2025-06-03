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

		parameters["Axis"] = std::make_unique<Float3Field>( "Axis", std::array<float, 3>{0.0f, 1.0f, 0.0f});
		parameters["Divisions"] = std::make_unique<IntField>("Divisions", 3, 3);
		parameters["Radius"] = std::make_unique<FloatField>("Radius", 1.0f, 0.0f);

		paramOrder.push_back("Axis");
		paramOrder.push_back("Divisions");
		paramOrder.push_back("Radius");
	}

	Mesh processOutput(uint32_t index) override;
	static Mesh createCircle(glm::vec3 axis, int divisions, float radius);
};