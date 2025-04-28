#include "App.h"

#include <stdexcept>

void App::run()
{
	euclideEngine.initEngine(1600, 1000, "Euclide");
	euclideEngine.exec();

}

