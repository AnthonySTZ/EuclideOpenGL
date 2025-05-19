#pragma once

#include "Node.h"

class Merge : public Node {

public:
	Merge() : Node("Merge") {
		inputsNb = 2;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index) override;
	void mergeToMesh(Mesh& mesh1, Mesh& mesh2);
};