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
		
	window = glfwCreateWindow(w, h, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed creating Window!");
	}
		
	glfwMakeContextCurrent(window);

}

EuclideWindow::~EuclideWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}