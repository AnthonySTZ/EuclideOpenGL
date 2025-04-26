#pragma once

#include "EuclideWindow.h"
#include <memory>

class EuclideEngine {

public:
	void initEngine();

	/* Window */
	void setWindowSize(int w, int h);
	void setWindowName(const char* name) { windowName = name; };
	void createWindow();

	/* Draw frame */
	void mainLoop();
	void drawFrame();

private:
	int WIDTH, HEIGHT;
	const char* windowName = "AppName";

	std::unique_ptr<EuclideWindow> euclideWindow;
};