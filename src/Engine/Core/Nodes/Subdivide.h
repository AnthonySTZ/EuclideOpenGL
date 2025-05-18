#pragma once

#include "Node.h"
#include "Fields/IntField.h"

class Subdivide : public Node {

public:
	Subdivide() : Node("Subdivide") {
		inputsNb = 1;
		outputsNb = 1;

		parameters["Iterations"] = std::make_unique<IntField>("Iterations", 1, 0);

		paramOrder.push_back("Iterations");
	}

	Mesh processOutput(uint32_t index) override;
	void subdivideMesh(Mesh& mesh);
};