#include "App.h"

#include <iostream>

#include "Engine/Core/Nodes/Cube.h"
#include "Engine/Core/Nodes/Transform.h"

#include "Engine/Core/Nodes/Scene.h"

int main() {

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

