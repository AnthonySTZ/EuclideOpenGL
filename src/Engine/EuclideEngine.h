#pragma once

#include "EuclideWindow.h"
#include "EuclideInterface.h"
#include <memory>

class EuclideEngine {

public:
	void initEngine(int w, int h, const char* name);

	/* Window */
	void createWindow();

	/* Draw frame */
	void mainLoop();
	void drawFrame();

private:
	int WIDTH, HEIGHT;
	const char* windowName = "AppName";

	std::unique_ptr<EuclideWindow> euclideWindow;
	std::unique_ptr<EuclideInterface> euclideInterface;
};