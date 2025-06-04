#pragma once

#include "Node.h"

#include "Fields/IntField.h"

class Subdivide : public Node {

public:
	Subdivide() : Node("Subdivide") {
		inputsNb = 1;
		outputsNb = 1;

		parameters["Subdivisions"] = std::make_unique<IntField>("Subdivisions", 1, 0);

		paramOrder.push_back("Subdivisions");
	};

	Mesh processOutput(uint32_t index) override;
	static Mesh subdivide(Mesh& mesh, int subdivisions);
};