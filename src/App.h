#pragma once

#include "Engine/EuclideEngine.h"

class App {

public:
	void run();

	Mesh::Builder createCube();

public:
	EuclideEngine euclideEngine{};
};