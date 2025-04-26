#include "EuclideEngine.h"

#include <stdexcept>
#include <iostream>

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
	euclideInterface = std::make_unique<EuclideInterface>(euclideWindow->getWindow());

}

/* --------------------- MAIN LOOP --------------------- */

void EuclideEngine::mainLoop() {

	while (!euclideWindow->shouldClose()) {

		glfwPollEvents();

		drawFrame();

	}

}

void EuclideEngine::drawFrame() {

	euclideInterface->createUI();

	int display_w, display_h;
	glfwGetFramebufferSize(euclideWindow->getWindow(), &display_w, &display_h); // Change to the viewport size maybe ?
	glViewport(0, 0, display_w, display_h);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	euclideInterface->renderUI();
	euclideWindow->swapBuffers();

}