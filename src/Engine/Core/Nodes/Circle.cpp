#include "Circle.h"

#include "../Utils.h"

Mesh Circle::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

	glm::vec3 axis = getParam<Float3Field>("Axis")->toVec3();
	int divisions = getParam<IntField>("Divisions")->getValue();
	float radius = getParam<FloatField>("Radius")->getValue();
	

	return createCircle(axis, divisions, radius);
}

Mesh Circle::createCircle(glm::vec3 axis, int divisions, float radius)
{
    return Mesh();
}