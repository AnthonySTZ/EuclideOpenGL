#pragma once

#include "EuclideWindow.h"
#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class EuclideEngine {

public:
	void initEngine();
	void initImGui();


	/* Window */
	void setWindowSize(int w, int h);
	void setWindowName(const char* name) { windowName = name; };
	void createWindow();

	/* Draw frame */
	void mainLoop();
	void drawFrame();
	void createDockSpace();


	/* cleanup */
	void cleanup();

private:
	int WIDTH, HEIGHT;
	const char* windowName = "AppName";

	std::unique_ptr<EuclideWindow> euclideWindow;
};