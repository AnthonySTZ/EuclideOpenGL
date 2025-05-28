#pragma once

#include "Node.h"

class BoundingBox : public Node {

public:
	struct BBox {
		glm::vec3 min{ 0.0 };
		glm::vec3 max{ 0.0 };
	};

	BoundingBox() : Node("BoundingBox") {
		inputsNb = 1;
		outputsNb = 1;
	};

	Mesh processOutput(uint32_t index) override;
	static BBox computeBoundingBox(Mesh& mesh);
};