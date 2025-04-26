#pragma once

#include <memory>

class EuclideEngine {

public:
	void initEngine();

	/* Window */
	void setWindowSize(int w, int h);
	void createWindow() {};

private:
	int WIDTH, HEIGHT;

	std::unique_ptr<EuclideWindow> euclideWindow;
};