#pragma once

#include "Node.h"

#include "Fields/IntField.h"

class SmoothNormals : public Node {

public:
	SmoothNormals() : Node("SmoothNormals") {
		inputsNb = 1;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh smoothNormals(Mesh mesh);
};