#pragma once


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class EuclideInterface {

public:
	EuclideInterface(GLFWwindow* window);
	~EuclideInterface();
	void createUI();
	void renderUI();

private:
	void createDockSpace();

};