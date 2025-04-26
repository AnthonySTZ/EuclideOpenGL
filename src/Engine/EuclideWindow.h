#pragma once

#include <GLFW/glfw3.h>
#include <string>

class EuclideWindow {

public:
	EuclideWindow(int w, int h, const char* name);
	~EuclideWindow();


private:
	GLFWwindow* window;
};
