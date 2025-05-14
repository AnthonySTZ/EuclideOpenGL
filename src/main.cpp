#include "App.h"

#include <iostream>

#include "Engine/Core/Nodes/Cube.h"
#include "Engine/Core/Nodes/Transform.h"

#include "Engine/Core/Nodes/Scene.h"

static void testNodes() {

	Cube cube;
	Cube cube1;
	Transform transform;

	std::cout << "Name: " << cube.getName() << " -- Inputs: " << cube.getInputsNb() << " -- Outputs: " << cube.getOutputsNb() << "\n";

	transform.setInput(0, &cube, 0);

	Node* inputNode = transform.getInput(0);
	if (inputNode != nullptr) {
		std::cout << "Transform -> input 0 : " << inputNode->getName() << "\n";
	}

	Mesh mesh = transform.processOutput(0);

	std::cout << "Transform output 0 : " << mesh.vertices.size() << " vertices" << "\n";

	Scene scene;

	scene.addNode(&cube);
	scene.addNode(&transform);
	scene.addNode(&cube1);

	std::cout << "Cube Name: " << cube.getName() << "\n";
	std::cout << "Transform Name: " << transform.getName() << "\n";
	std::cout << "Cube Name: " << cube1.getName() << "\n";
}

int main() {

	/*testNodes();
	return EXIT_SUCCESS;*/

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

