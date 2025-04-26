#pragma once

#include <GLFW/glfw3.h>
#include <string>

class EuclideWindow {

public:
	EuclideWindow(int w, int h, const char* name);
	~EuclideWindow();

	bool shouldClose() { return glfwWindowShouldClose(window); };
	void swapBuffers() { glfwSwapBuffers(window); };

private:
	GLFWwindow* window;
};
