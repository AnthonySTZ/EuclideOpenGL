#pragma once

#include "Node.h"

class Null : public Node {

public:
	Null() : Node("Null") {
		inputsNb = 1;
		outputsNb = 1;
	};

	Mesh& processOutput(uint32_t index, bool *updateDirty = nullptr) override;
private:
	Mesh cachedMesh;
};