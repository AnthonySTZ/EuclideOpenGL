#pragma once

#include "EuclideRenderer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <chrono>
#include <memory>


class EuclideInterface {

	using clock = std::chrono::high_resolution_clock;

public:
	EuclideInterface(GLFWwindow* window);
	void initImGui(GLFWwindow* window);
	void createRenderer();
	~EuclideInterface();
	void drawFrame();
	void createUI();
	void createViewport();
	void createNodeGraph();
	void renderUI();

	bool hasViewportResized() const { return viewportResized; };
	int getViewportWidth() const { return viewportWidth; };
	int getViewportHeight() const { return viewportHeight; };

private:
	/* VIEWPORT */
	bool viewportResized=false;
	int viewportWidth = 1200;
	int viewportHeight = 800;

	/* FPS */
	std::chrono::steady_clock::time_point lastTime = clock::now();
	float fpsIntervalInSeconds = 0.5f;
	int frameCount = 0;
	float elapsedTime = 0.0f;
	int fpsShow = 0;

	void createDockSpace();
	void calcFps();

	std::unique_ptr<EuclideRenderer> renderer;

};