#include "App.h"

#include <iostream>

#include "Engine/Core/Nodes/Cube.h"

int main() {

	Cube cube;

	std::cout << "Name: " << cube.getName().c_str() << " -- Inputs: " << cube.getInputsNb() << " -- Outputs: " << cube.getOutputsNb() << "\n";


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