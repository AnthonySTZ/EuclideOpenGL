#pragma once

#include "Node.h"
#include "Fields/ComboField.h"
#include "Fields/IntField.h"
#include "Fields/FloatField.h"

class QuadSphere : public Node {

public:
	QuadSphere() : Node("QuadSphere") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Subdivisions"] = std::make_unique<IntField>("Subdivisions", 2, 0);
		parameters["Radius"] = std::make_unique<FloatField>("Radius", 1.0f, 0.0f);

		paramOrder.push_back("Subdivisions");
		paramOrder.push_back("Radius");
	}

	Mesh& processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh createQuadSphere(int subdivisions, float radius);

private: 
	Mesh cachedMesh;
};