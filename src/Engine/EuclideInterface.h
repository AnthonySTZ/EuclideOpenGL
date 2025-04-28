#pragma once


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class EuclideInterface {

public:
	EuclideInterface(GLFWwindow* window);
	~EuclideInterface();
	void createUI(ImTextureID renderTexture);
	void renderUI();

	bool hasViewportResized() const { return viewportResized; };
	int getViewportWidth() const { return viewportWidth; };
	int getViewportHeight() const { return viewportHeight; };

private:
	bool viewportResized;
	int viewportWidth, viewportHeight;

	void createDockSpace();

};