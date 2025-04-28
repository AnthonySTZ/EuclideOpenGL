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


/* --------------------- RENDERING --------------------- */

void EuclideEngine::exec()
{

	const char* vertexShaderSrc =
		"#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}\0";

	const char* fragmentShaderSrc =
		"#version 330 core\n"
		"out vec4 outColor;\n"
		"void main() {\n"
		"	outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, 0);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
		std::cout << infoLog << "\n";
		throw std::runtime_error("Shader compilation failed");
	}


	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, 0);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
		std::cout << infoLog << "\n";
		throw std::runtime_error("Shader compilation failed");
	}

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

}