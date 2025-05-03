#pragma once

#include "EuclideWindow.h"
#include "EuclideInterface.h"
#include <memory>

class EuclideEngine {

public:
	void initEngine(int w, int h, const char* name);

	/* Window */
	void createWindow(int w, int h);

	void updateModel(const EuclideModel::Builder& builder);

	/* Rendering */
	void exec();
	void mainLoop();

private:
	const char* windowName = "AppName";

	std::unique_ptr<EuclideWindow> euclideWindow;
	std::unique_ptr<EuclideInterface> euclideInterface;
};