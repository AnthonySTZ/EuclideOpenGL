#include "QuadSphere.h"

#include "../Utils.h"

#include "Cube.h"
#include "Subdivide.h"


Mesh QuadSphere::processOutput(uint32_t index, bool *updateDirty)
{
	Timer timer{ nodeName.c_str() };

	if (!hasParamsChanged()) return cachedMesh;

	int subd = getParam<IntField>("Subdivisions")->getValue();
	float radius = getParam<FloatField>("Radius")->getValue();

	cachedMesh = createQuadSphere(subd, radius);

	return cachedMesh;
}


Mesh QuadSphere::createQuadSphere(int subdivisions, float radius)
{
    Mesh cube = Cube::createCube({0, 0, 0}, {radius, radius, radius});
    return Subdivide::subdivide(cube, subdivisions);
}