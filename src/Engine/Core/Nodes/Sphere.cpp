#include "Sphere.h"

#include "../Utils.h"

#include <glm/gtc/constants.hpp>

Mesh Sphere::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

	int rows = getParam<IntField>("Rows")->getValue();
	int columns = getParam<IntField>("Columns")->getValue();
	float radius = getParam<FloatField>("Radius")->getValue();
	
	return createUVSphere(rows, columns, radius);
}

Mesh Sphere::createUVSphere(int rows, int columns, float radius)
{

    if (columns < 3) return Mesh();
    if (rows < 3) return Mesh();

    Timer timer{ "createUVSphere" };

    Mesh::Builder builder;

    uint32_t topPointId = builder.addPoint( {0, 1, 0} ); // Add top point

    for (int i=0; i<rows-1; i++){

        double phi = glm::pi<double>() * (double)(i+1) / (double)rows;
        for (int j=0; j < columns; j++){
            double theta = glm::two_pi<double>() * (double)j / (double)columns;
            glm::vec3 pos = {
                glm::sin(phi) * glm::cos(theta),
                glm::cos(phi),
                glm::sin(phi) * glm::sin(theta)
            };
            builder.addPoint(pos);
        }

    }

    uint32_t bottomPointId = builder.addPoint({0, -1, 0}); // Add bottom point

    // add top / bottom triangles
    for (int i=0; i < columns; i++){
        uint32_t i0 = i + 1;
        uint32_t i1 = (i + 1) % columns + 1;
        builder.addFace({i1, i0, topPointId}); // Top triangle

        i0 = i + columns * (rows - 2) + 1;
        i1 = (i + 1) % columns + columns * (rows - 2) + 1;
        builder.addFace({bottomPointId, i0, i1}); // Bottom triangle
    }

    for (int j = 0; j < rows - 2; j++)
    {
        uint32_t j0 = j * columns + 1;
        uint32_t j1 = (j + 1) * columns + 1;

        for (int i = 0; i < columns; i++) {
            uint32_t i0 = j0 + i;
            uint32_t i1 = j0 + (i + 1) % columns;
            uint32_t i2 = j1 + (i + 1) % columns;
            uint32_t i3 = j1 + i;
            builder.addFace({i0, i1, i2, i3});
        }

    }

    return Mesh{builder};
}