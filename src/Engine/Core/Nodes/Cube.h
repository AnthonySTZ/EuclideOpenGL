#pragma once

#include "Node.h"

class Cube : public Node {

public:
	Cube() : Node("Cube") {
		inputsNb = 0;
		outputsNb = 1;
	};
	
};