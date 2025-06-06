#pragma once

#include "Node.h"
#include "Fields/Float3Field.h"
#include "Fields/FloatField.h"
#include "Fields/IntField.h"
#include "Fields/BooleanField.h"

class Cylinder : public Node {

public:
	Cylinder() : Node("Cylinder") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Height"] = std::make_unique<FloatField>("Height", 1.0f, 0.0f);
		parameters["RadiusTop"] = std::make_unique<FloatField>("Radius Top", 1.0f, 0.0f);
		parameters["RadiusBottom"] = std::make_unique<FloatField>("Height Bottom", 1.0f, 0.0f);
		parameters["Divisions"] = std::make_unique<IntField>("Divisions", 8, 3);
		parameters["Capped"] = std::make_unique<BooleanField>("Capped", false);
		parameters["Translate"] = std::make_unique<Float3Field>("Translate");

		paramOrder.push_back("Height");
		paramOrder.push_back("RadiusTop");
		paramOrder.push_back("RadiusBottom");
		paramOrder.push_back("Divisions");
		paramOrder.push_back("Capped");
		paramOrder.push_back("Translate");
	}

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh createCylinder(glm::vec3 position, glm::vec2 radius, float height, int divisions, bool capped);
private: 
	Mesh cachedMesh;
};