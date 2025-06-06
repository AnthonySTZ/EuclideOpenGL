#pragma once

#include "Node.h"

class VisualizeNormals : public Node {

public:
	VisualizeNormals() : Node("VisualizeNormals") {
		inputsNb = 1;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
};