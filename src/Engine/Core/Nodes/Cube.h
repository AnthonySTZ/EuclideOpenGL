#pragma once

#include "Node.h"
#include "Fields/Float3Field.h"

class Cube : public Node {

public:
	Cube() : Node("Cube") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Size"] = std::make_unique<Float3Field>( "Size", std::array<float, 3>{1.0f, 1.0f, 1.0f}, 0.0f);
		parameters["Translate"] = std::make_unique<Float3Field>("Translate");

		paramOrder.push_back("Size");
		paramOrder.push_back("Translate");
	}

	Mesh processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh createCube(glm::vec3 position, glm::vec3 size);
private: 
	Mesh cachedMesh;
};