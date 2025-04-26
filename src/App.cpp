#include "App.h"

#include <stdexcept>

//void App::initWindow(int width, int height)
//{
//	if (width <= 0 || height <= 0) {
//		throw std::runtime_error("Window size invalid!");
//	}
//
//	WIDTH = width;
//	HEIGHT = height;
//
//	if (!glfwInit()) {
//		throw std::runtime_error("Failed initialized GLFW!");
//	}
//
//	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		throw std::runtime_error("Failed creating Window!");
//	}
//
//	glfwMakeContextCurrent(window);
//}

void App::run()
{

	euclideEngine.setWindowSize(1200, 800);

	/*while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}

	glfwTerminate();*/

}

