#include "Sphere.h"

#include "../Utils.h"

#include <glm/gtc/constants.hpp>

Mesh Sphere::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

	int rows = getParam<IntField>("Rows")->getValue();
	int columns = getParam<IntField>("Columns")->getValue();
	float radius = getParam<FloatField>("Radius")->getValue();
	
	return createSphere(rows, columns, radius);
}

Mesh Sphere::createSphere(int rows, int columns, float radius)
{
    return Mesh();
}