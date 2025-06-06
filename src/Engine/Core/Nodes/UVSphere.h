#pragma once

#include "Node.h"
#include "Fields/ComboField.h"
#include "Fields/IntField.h"
#include "Fields/FloatField.h"

class UVSphere : public Node {

public:
	UVSphere() : Node("UVSphere") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Rows"] = std::make_unique<IntField>("Rows", 8, 3);
		parameters["Columns"] = std::make_unique<IntField>("Columns", 16, 3);
		parameters["Radius"] = std::make_unique<FloatField>("Radius", 1.0f, 0.0f);

		paramOrder.push_back("Rows");
		paramOrder.push_back("Columns");
		paramOrder.push_back("Radius");
	}

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh createUVSphere(int rows, int columns, float radius);
private: 
	Mesh cachedMesh;
};