#pragma once

#include "Node.h"

#include "Fields/Float3Field.h"

class Transform : public Node {

public:
	Transform() : Node("Transform") {
		inputsNb = 1;
		outputsNb = 1;

		parameters["Translate"] = std::make_unique<Float3Field>("Translate");
		parameters["Scale"] = std::make_unique<Float3Field>("Scale", std::array<float, 3>{1.0f, 1.0f, 1.0f});
		parameters["Rotate"] = std::make_unique<Float3Field>("Rotate");

		paramOrder.push_back("Translate");
		paramOrder.push_back("Scale");
		paramOrder.push_back("Rotate");
	};

	Mesh& processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh translateMesh(Mesh mesh, glm::vec3 translation);
	static Mesh scaleMesh(Mesh mesh, glm::vec3 scale);
	static Mesh rotateMesh(Mesh mesh, glm::vec3 rotation);

private:
	Mesh cachedMesh;
};