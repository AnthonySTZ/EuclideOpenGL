#include "EuclideEngine.h"

#include <stdexcept>
#include <iostream>

void EuclideEngine::initEngine(int w, int h, const char* name)
{
	windowName = name;
	createWindow(w, h);
}


/* --------------------- WINDOW --------------------- */

void EuclideEngine::createWindow(int w, int h)
{

	euclideWindow = std::make_unique<EuclideWindow>(w, h, windowName);
	euclideInterface = std::make_unique<EuclideInterface>(euclideWindow->getWindow());

}

void EuclideEngine::updateModel(Mesh::Builder& builder)
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