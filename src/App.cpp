#include "App.h"

#include <stdexcept>

#include "Engine/Core/Geometry.h"
#include <iostream>

void App::run()
{
	euclideEngine.initEngine(1600, 1000, "Euclide");
	euclideEngine.exec();
}
