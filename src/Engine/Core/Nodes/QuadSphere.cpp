#include "QuadSphere.h"

#include "../Utils.h"

#include "Cube.h"
#include "Subdivide.h"


Mesh QuadSphere::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

	int subd = getParam<IntField>("Subdivisions")->getValue();
	float radius = getParam<FloatField>("Radius")->getValue();

	return createQuadSphere(subd, radius);
}


Mesh QuadSphere::createQuadSphere(int subdivisions, float radius)
{
    Mesh cube = Cube::createCube({0, 0, 0}, {radius, radius, radius});
    return Subdivide::subdivide(cube, subdivisions);
}