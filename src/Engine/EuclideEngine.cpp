#include "EuclideEngine.h"

#include <stdexcept>

void EuclideEngine::initEngine()
{
	createWindow();
}

/* --------------------- WINDOW --------------------- */

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

void EuclideEngine::createWindow()
{

	euclideWindow = std::make_unique<EuclideWindow>(WIDTH, HEIGHT, windowName);

}

/* --------------------- MAIN LOOP --------------------- */

void EuclideEngine::mainLoop() {

	while (!euclideWindow->shouldClose()) {

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		euclideWindow->swapBuffers();

	}

}