#include "App.h"

#include <iostream>

#include "Engine/Core/Nodes/Cube.h"
#include "Engine/Core/Nodes/Transform.h"

int main() {

	Cube cube;
	Transform transform;

	std::cout << "Name: " << cube.getName().c_str() << " -- Inputs: " << cube.getInputsNb() << " -- Outputs: " << cube.getOutputsNb() << "\n";

	transform.setInput(0, &cube, 0);

	Node* inputNode = transform.getInput(0);
	if (inputNode != nullptr) {
		std::cout << "Transform -> input 0 : " << inputNode->getName().c_str() << "\n";
	}

	Mesh mesh = transform.processOutput(0);

	std::cout << "Mesh : " << mesh.vertices.size() << " vertices" << "\n";

	return EXIT_SUCCESS;
	App app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}