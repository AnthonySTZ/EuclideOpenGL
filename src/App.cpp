#include "App.h"

#include <stdexcept>

void App::run()
{

	euclideEngine.setWindowSize(1200, 800);
	euclideEngine.setWindowName("Euclide");
	euclideEngine.createWindow();

	euclideEngine.mainLoop();

}

