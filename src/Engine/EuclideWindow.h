#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class EuclideWindow {

public:
	EuclideWindow(int w, int h, const char* name);
	~EuclideWindow();

	bool shouldClose() { return glfwWindowShouldClose(window); };
	void swapBuffers() { glfwSwapBuffers(window); };
	
	GLFWwindow* getWindow() const { return window; };

private:
	GLFWwindow* window;
};
