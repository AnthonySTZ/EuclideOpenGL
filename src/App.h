#pragma once

#include "Engine/EuclideEngine.h"

class App {

public:
	void run();

	void mainLoop() const;

public:
	EuclideEngine euclideEngine{};
};