#pragma once

#include "Node.h"
#include "Fields/Float3Field.h"
#include "Fields/IntField.h"

class Line : public Node {

public:
	Line() : Node("Line") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Axis"] = std::make_unique<Float3Field>( "Axis", std::array<float, 3>{0.0f, 1.0f, 0.0f});
		parameters["Divisions"] = std::make_unique<IntField>("Divisions", 2, 2);

		paramOrder.push_back("Axis");
		paramOrder.push_back("Divisions");
	}

	Mesh processOutput(uint32_t index) override;
	static Mesh createLine(glm::vec3 axis, int divisions);
};