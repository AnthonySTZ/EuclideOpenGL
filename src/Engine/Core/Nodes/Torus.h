#pragma once

#include "Node.h"
#include "Fields/IntField.h"
#include "Fields/FloatField.h"

class Torus : public Node {

public:
	Torus() : Node("Torus") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["nRings"] = std::make_unique<IntField>("Number of Rings", 16, 3);
		parameters["ringSubd"] = std::make_unique<IntField>("Rings Subdivisions", 8, 3);
		parameters["ringRadius"] = std::make_unique<FloatField>("Ring Radius", 1.0f, 0.0f);
		parameters["torusRadius"] = std::make_unique<FloatField>("Torus Radius", 1.0f, 0.0f);

		paramOrder.push_back("nRings");
		paramOrder.push_back("ringSubd");
		paramOrder.push_back("ringRadius");
		paramOrder.push_back("torusRadius");
	}

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh createTorus(int nRings, int ringSubd, float innerRadius, float outerRadius);
private: 
	Mesh cachedMesh;
};