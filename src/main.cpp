#include "App.h"

#include <iostream>

#include "Engine/Core/Nodes/Cube.h"

int main() {

	Cube cubeTop;
	Cube cube;

	std::cout << "Name: " << cube.getName().c_str() << " -- Inputs: " << cube.getInputsNb() << " -- Outputs: " << cube.getOutputsNb() << "\n";

	cubeTop.setName("CubeTop");

	cube.setInput(0, &cubeTop, 0);

	Node* inputNode = cube.getInput(0);
	if (inputNode != nullptr) {
		std::cout << "Cube -> input 0 : " << inputNode->getName().c_str() << "\n";
	}

	Mesh mesh = cube.processOutput(0);

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