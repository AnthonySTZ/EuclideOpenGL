#include "App.h"

#include <stdexcept>

#include "Engine/Geometry.h"
#include <iostream>

void App::run()
{

    Face face{};
    face.vertexIndices = {0, 1, 2};

    Face face2{};
    face2.vertexIndices = { 0, 2, 3 };

    std::vector<Face> faces = { face, face2 };
    
    Mesh::Builder builder;

    std::vector<Vertex> vertices = { 
        { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 },
        { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 },
        { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 },
        { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 },
    };

    builder.vertices = vertices;
    builder.faces = faces;

    Mesh mesh{ builder };

    return;
    EuclideModel::Builder cube = createCube();

	euclideEngine.initEngine(1600, 1000, "Euclide");
	euclideEngine.updateModel(cube);
	euclideEngine.exec();

}

EuclideModel::Builder App::createCube() {

    EuclideModel::Builder modelBuilder{};
    // Duplicate vertices to have hard normals
    modelBuilder.vertices = {
        // Front face (normal: 0, 0, 1)
        { {-0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, 1.0f} },
        { { 0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, 1.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, 1.0f} },

        // Back face (normal: 0, 0, -1)
        { {-0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, -1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, -1.0f} },
        { { 0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, -1.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 0.0f, -1.0f} },

        // Left face (normal: -1, 0, 0)
        { {-0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f, 0.0f, 0.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f, 0.0f, 0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f, 0.0f, 0.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {-1.0f, 0.0f, 0.0f} },

        // Right face (normal: 1, 0, 0)
        { { 0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f, 0.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f, 0.0f} },

        // Top face (normal: 0, 1, 0)
        { {-0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 1.0f, 0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 1.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 1.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, 1.0f, 0.0f} },

        // Bottom face (normal: 0, -1, 0)
        { {-0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, -1.0f, 0.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, -1.0f, 0.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, -1.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.8f, 0.8f, 0.8f}, {0.0f, -1.0f, 0.0f} },
    };

    modelBuilder.indices = {
        // Front
        0, 1, 2,  2, 1, 3,
        // Back
        4, 5, 6,  6, 5, 7,
        // Left
        8, 9, 10,  10, 9, 11,
        // Right
        12, 13, 14,  14, 13, 15,
        // Top
        16, 17, 18,  18, 17, 19,
        // Bottom
        20, 21, 22,  22, 21, 23
    };


    return modelBuilder;
}

EuclideModel::Builder App::createSphere(float radius, int sectorCount, int stackCount) {
    EuclideModel::Builder modelBuilder{};
    const float PI = 3.14159265359f;

    // Generate vertices
    for (int i = 0; i <= stackCount; ++i) {
        float stackAngle = PI / 2.0f - i * (PI / stackCount); // from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            float sectorAngle = j * (2.0f * PI / sectorCount); // 0 to 2pi

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);
            glm::vec3 pos = { x, y, z };
            glm::vec3 normal = glm::normalize(pos); // for smooth shading
            glm::vec3 color = { 0.8f, 0.8f, 0.8f };

            modelBuilder.vertices.push_back({ pos, color, normal });
        }
    }

    // Generate indices
    for (int i = 0; i < stackCount; ++i) {
        int k1 = i * (sectorCount + 1);     // beginning of current stack
        int k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                modelBuilder.indices.push_back(k1);
                modelBuilder.indices.push_back(k2);
                modelBuilder.indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                modelBuilder.indices.push_back(k1 + 1);
                modelBuilder.indices.push_back(k2);
                modelBuilder.indices.push_back(k2 + 1);
            }
        }
    }

    return modelBuilder;
}
