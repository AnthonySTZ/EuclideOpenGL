#include "App.h"

#include <iostream>

#include "Engine/Core/Nodes/tests/Benchmarks.h"

// #define NODES_BENCHMARKS

int main() {

	#ifdef NODES_BENCHMARKS
		Benchmarks::benchNodes();
		return EXIT_SUCCESS;
	#endif
	
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

