#include "App.h"

#include <stdexcept>

void App::run()
{

	euclideEngine.setWindowSize(1600, 1000);
	euclideEngine.setWindowName("Euclide");
	euclideEngine.initEngine();

	euclideEngine.mainLoop();

}

