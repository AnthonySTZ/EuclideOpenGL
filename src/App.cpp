#include "App.h"

#include <stdexcept>

#include <iostream>

void App::run()
{
	euclideEngine.initEngine(1600, 1000, "Euclide");
	euclideEngine.exec();
}
