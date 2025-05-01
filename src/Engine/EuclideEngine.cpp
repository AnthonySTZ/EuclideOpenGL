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

void EuclideEngine::updateModel(const EuclideModel::Builder& builder)
{

	model.update(builder);

}


/* --------------------- RENDERING --------------------- */

void EuclideEngine::createRenderer()
{

	euclideRenderer = std::make_unique<EuclideRenderer>(
		"src/Engine/shaders/vertShader.vert",
		"src/Engine/shaders/fragShader.frag",
		&model);

}

void EuclideEngine::exec()
{

	euclideRenderer->initBuffers();
	euclideRenderer->initFramebuffer();

	mainLoop();
}

/* --------------------- MAIN LOOP --------------------- */

void EuclideEngine::mainLoop() {

	while (!euclideWindow->shouldClose()) {


		glfwPollEvents();

		drawFrame();
		
		euclideWindow->swapBuffers();
	}

}

void EuclideEngine::drawFrame() {

	euclideInterface->createUI((ImTextureID)(intptr_t)euclideRenderer->getRenderTexture());
	if (euclideInterface->hasViewportResized()) {
		euclideRenderer->resizeFrameBuffer(euclideInterface->getViewportWidth(), euclideInterface->getViewportHeight());
	}

	euclideRenderer->draw();

	euclideInterface->renderUI();

}