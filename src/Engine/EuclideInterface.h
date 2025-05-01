#pragma once


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <chrono>


class EuclideInterface {

	using clock = std::chrono::high_resolution_clock;

public:
	EuclideInterface(GLFWwindow* window);
	~EuclideInterface();
	void createUI(ImTextureID renderTexture);
	void renderUI();

	bool hasViewportResized() const { return viewportResized; };
	int getViewportWidth() const { return viewportWidth; };
	int getViewportHeight() const { return viewportHeight; };

private:
	bool viewportResized=false;
	int viewportWidth = 1200;
	int viewportHeight = 800;
	std::chrono::steady_clock::time_point lastTime = clock::now();
	std::chrono::steady_clock::time_point restartTime = clock::now();
	float fpsIntervalInSeconds = 0.5f;
	float fpsCounter = 0;
	int fpsDivideBy = 1;
	int fpsShow = 0;

	void createDockSpace();

};