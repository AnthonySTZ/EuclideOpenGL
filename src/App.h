#pragma once

#include "Engine/EuclideEngine.h"

class App {

public:
	void run();

	Mesh createCube();

public:
	EuclideEngine euclideEngine{};
};