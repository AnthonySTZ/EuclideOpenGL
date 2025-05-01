#include "App.h"

#include <stdexcept>

void App::run()
{
	EuclideModel::Builder modelBuilder{};
	modelBuilder.vertices = {
		{ { -0.5f,  0.5f,  0.0f}, { 1.0, 0.0, 0.0 } },
		{ { -0.5f, -0.5f,  0.0f}, { 1.0, 1.0, 0.0 } },
		{ {  0.5f,  0.5f,  0.0f}, { 1.0, 0.0, 1.0 } },
		{ {  0.5f, -0.5f,  0.0f}, { 0.0, 1.0, 1.0 } }
	};

	modelBuilder.indices = {
		0, 1, 2,
		2, 1, 3
	};

	euclideEngine.createModel(modelBuilder);
	euclideEngine.initEngine(1600, 1000, "Euclide");
	euclideEngine.exec();

}

