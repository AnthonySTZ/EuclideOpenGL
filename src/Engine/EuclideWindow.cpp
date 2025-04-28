#include "EuclideWindow.h"

#include <stdexcept>

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLAD!");
	}
}

EuclideWindow::~EuclideWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}