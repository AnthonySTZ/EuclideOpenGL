#include "EuclideEngine.h"

#include <stdexcept>
#include <iostream>

void EuclideEngine::initEngine(int w, int h, const char* name)
{
	WIDTH = w;
	HEIGHT = h;
	windowName = name;
	createWindow();
	createRenderer();
}


/* --------------------- WINDOW --------------------- */

void EuclideEngine::createWindow()
{

	euclideWindow = std::make_unique<EuclideWindow>(WIDTH, HEIGHT, windowName);
	euclideInterface = std::make_unique<EuclideInterface>(euclideWindow->getWindow());

}


/* --------------------- RENDERING --------------------- */

void EuclideEngine::createRenderer()
{

	euclideRenderer = std::make_unique<EuclideRenderer>(
		"src/Engine/shaders/vertShader.vert",
		"src/Engine/shaders/fragShader.frag");

}

void EuclideEngine::exec()
{

	euclideRenderer->initBuffers();

	mainLoop();
}

/* --------------------- MAIN LOOP --------------------- */

void EuclideEngine::mainLoop() {

	while (!euclideWindow->shouldClose()) {

		glfwPollEvents();

		//euclideInterface->createUI();

		drawFrame();

		//euclideInterface->renderUI();
		euclideWindow->swapBuffers();
	}

}

void EuclideEngine::drawFrame() {

	int display_w, display_h;
	glfwGetFramebufferSize(euclideWindow->getWindow(), &display_w, &display_h); // Change to the viewport size maybe ?
	glViewport(0, 0, display_w, display_h);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	euclideRenderer->draw();

}