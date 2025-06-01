#pragma once

#include "Node.h"

#include "Fields/IntField.h"

class HardenNormals : public Node {

public:
	HardenNormals() : Node("HardenNormals") {
		inputsNb = 1;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index) override;
	static Mesh hardenNormals(Mesh mesh);
};