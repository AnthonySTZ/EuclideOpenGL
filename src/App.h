#pragma once

#include <GLFW/glfw3.h>

class App {

public:
	App() = default;

	void initWindow(int width, int height);
	void run();

private:
	int WIDTH, HEIGHT;
	GLFWwindow* window;
};