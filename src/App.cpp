#include "App.h"

#include <stdexcept>

#include "Engine/Core/Geometry.h"
#include <iostream>

void App::run()
{
    Mesh::Builder cube = createCube();

	euclideEngine.initEngine(1600, 1000, "Euclide");
	euclideEngine.updateModel(cube);
	euclideEngine.exec();

}

Mesh::Builder App::createCube() {

    Mesh::Builder modelBuilder{};

    modelBuilder.vertices = {
        // Front face (0-3)
        { {-0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, 1.0f} },
        { { 0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, 1.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, 1.0f} },

        // Back face (4-7)
        { {-0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, -1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, -1.0f} },
        { { 0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, -1.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  0.0f, -1.0f} },

        // Left face (8-11)
        { {-0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f,  0.0f,  0.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f,  0.0f,  0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f,  0.0f,  0.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f,  0.0f,  0.0f} },

        // Right face (12-15)
        { { 0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 1.0f,  0.0f,  0.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 1.0f,  0.0f,  0.0f} },
        { { 0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 1.0f,  0.0f,  0.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 1.0f,  0.0f,  0.0f} },

        // Top face (16-19)
        { {-0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  1.0f,  0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  1.0f,  0.0f} },
        { { 0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  1.0f,  0.0f} },
        { { 0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f,  1.0f,  0.0f} },

        // Bottom face (20-23)
        { {-0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f, -1.0f,  0.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f, -1.0f,  0.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f, -1.0f,  0.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, { 0.0f, -1.0f,  0.0f} },
    };

    Face faceFront;
    faceFront.vertexIndices = { 0, 1, 3, 2 };
    Face faceBack;
    faceBack.vertexIndices = { 4, 6, 7, 5 };
    Face faceLeft;
    faceLeft.vertexIndices = { 8, 9, 11, 10 };
    Face faceRight;
    faceRight.vertexIndices = { 12, 14, 15, 13 };
    Face faceTop;
    faceTop.vertexIndices = { 16, 18, 19, 17 };
    Face faceBottom;
    faceBottom.vertexIndices = { 20, 21, 23, 22 };


    modelBuilder.faces = {
        faceFront, faceBack, faceLeft, faceRight, faceTop, faceBottom
    };


    return modelBuilder;
}