#pragma once

#include "Node.h"

#include "Fields/Float3Field.h"
#include "Fields/IntField.h"
#include "Fields/FloatField.h"

class PointGenerate : public Node {

public:
	PointGenerate() : Node("PointGenerate") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["nPoints"] = std::make_unique<IntField>("Nb of points", 1, 1);
		parameters["Position"] = std::make_unique<Float3Field>("Position");

		paramOrder.push_back("nPoints");
		paramOrder.push_back("Position");
	};

	Mesh& processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh generatePoints(int nb, glm::vec3 position = glm::vec3{0.0});
private: 
	Mesh cachedMesh;
};