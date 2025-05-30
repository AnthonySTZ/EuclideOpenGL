#include "EuclideWindow.h"

#include <stdexcept>

#include <iostream>

EuclideWindow::EuclideWindow(int w, int h, const char* name)
{

	if (w <= 0 || h <= 0) {
		throw std::runtime_error("Window size invalid!");
	}
		
	if (!glfwInit()) {
		throw std::runtime_error("Failed initialized GLFW!");
	}
		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(w, h, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed creating Window!");
	}
		
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0); // Disable Vsync

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLAD!");
	}

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << err << std::endl;
	}
}

EuclideWindow::~EuclideWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}