#include "App.h"

#include <stdexcept>

void App::run()
{
	EuclideModel::Builder modelBuilder{};
    modelBuilder.vertices = {
    { {-0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f} }, // Front-top-left
    { {-0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f} }, // Front-bottom-left
    { { 0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f} }, // Front-top-right
    { { 0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f} }, // Front-bottom-right
                              
    { {-0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f} }, // Back-top-left
    { {-0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f} }, // Back-bottom-left
    { { 0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f} }, // Back-top-right
    { { 0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f} }  // Back-bottom-right
    };

    modelBuilder.indices = {
        // Front face
        0, 1, 2,  2, 1, 3,
        // Back face
        4, 5, 6,  6, 5, 7,
        // Left face
        4, 0, 1,  1, 5, 4,
        // Right face
        2, 3, 6,  6, 3, 7,
        // Top face
        4, 0, 2,  2, 6, 4,
        // Bottom face
        1, 3, 5,  5, 3, 7
    };

	euclideEngine.initEngine(1600, 1000, "Euclide");
	euclideEngine.updateModel(modelBuilder);
	euclideEngine.exec();

}

