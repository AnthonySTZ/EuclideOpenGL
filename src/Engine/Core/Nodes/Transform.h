#pragma once

#include "Node.h"

class Transform : public Node {

public:
	Transform() : Node("Transform") {
		inputsNb = 1;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index) override;
};