#include "EuclideEngine.h"

#include <stdexcept>

void EuclideEngine::initEngine()
{
	createWindow();
}

void EuclideEngine::setWindowSize(int w, int h)
{
	if (w <= 0) {
		throw std::runtime_error("Invalid Width!");
	}

	if (h <= 0) {
		throw std::runtime_error("Invalid Height!");
	}

	WIDTH = w;
	HEIGHT = h;
}
