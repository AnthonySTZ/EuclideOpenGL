#include "EuclideEngine.h"

#include <stdexcept>
#include <iostream>

void EuclideEngine::initEngine(int w, int h, const char* name)
{
	WIDTH = w;
	HEIGHT = h;
	windowName = name;
	createWindow();
}


/* --------------------- WINDOW --------------------- */

void EuclideEngine::createWindow()
{

	euclideWindow = std::make_unique<EuclideWindow>(WIDTH, HEIGHT, windowName);
	euclideInterface = std::make_unique<EuclideInterface>(euclideWindow->getWindow());

}

void EuclideEngine::updateModel(const EuclideModel::Builder& builder)
{

	euclideInterface->updateModel(builder);

}

/* --------------------- RENDERING --------------------- */

void EuclideEngine::exec()
{
	mainLoop();
}

/* --------------------- MAIN LOOP --------------------- */

void EuclideEngine::mainLoop() {

	while (!euclideWindow->shouldClose()) {

		glfwPollEvents();

		euclideInterface->drawFrame();
		
		euclideWindow->swapBuffers();
	}

}