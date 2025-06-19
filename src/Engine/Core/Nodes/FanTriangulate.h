#pragma once

#include "Node.h"

class FanTriangulate : public Node {

public:
	FanTriangulate() : Node("FanTriangulate") {
		inputsNb = 1;
		outputsNb = 1;
	};

	Mesh& processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh fanTriangulate(Mesh& mesh);
private: 
	Mesh cachedMesh;
};