#pragma once

#include "Node.h"

class Merge : public Node {

public:
	Merge() : Node("Merge") {
		inputsNb = 2;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh mergeToMesh(Mesh& mesh_1, Mesh& mesh_2);
private: 
	Mesh cachedMesh;
};