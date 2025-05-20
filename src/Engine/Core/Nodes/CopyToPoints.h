#pragma once

#include "Node.h"

class CopyToPoints : public Node {

public:
	CopyToPoints() : Node("CopyToPoints") {
		inputsNb = 2;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index) override;
	Mesh copyToPoints(Mesh& mesh_1, Mesh& mesh_2);
};