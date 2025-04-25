#pragma once

#include <GLFW/glfw3.h>

class App {

public:

	void initWindow(int width, int height);

private:
	int WIDTH, HEIGHT;
	GLFWwindow* window;
};