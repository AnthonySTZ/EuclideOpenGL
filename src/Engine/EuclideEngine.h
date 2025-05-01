#pragma once

#include "EuclideWindow.h"
#include "EuclideInterface.h"
#include "EuclideRenderer.h"
#include <memory>

class EuclideEngine {

public:
	void initEngine(int w, int h, const char* name);

	/* Window */
	void createWindow();

	void createModel(const EuclideModel::Builder& builder);

	/* Rendering */
	void createRenderer();
	void exec();
	void mainLoop();
	void drawFrame();

private:
	int WIDTH, HEIGHT;
	const char* windowName = "AppName";

	std::unique_ptr<EuclideWindow> euclideWindow;
	std::unique_ptr<EuclideInterface> euclideInterface;
	std::unique_ptr<EuclideRenderer> euclideRenderer;
	std::vector<EuclideModel> models;
};