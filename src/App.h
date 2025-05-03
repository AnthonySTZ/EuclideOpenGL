#pragma once

#include "Engine/EuclideEngine.h"

class App {

public:
	void run();

	EuclideModel::Builder createCube();

	EuclideModel::Builder createSphere(float radius = 0.5f, int sectorCount = 16, int stackCount = 8);

public:
	EuclideEngine euclideEngine{};
};