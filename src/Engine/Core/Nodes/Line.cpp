#include "Line.h"

#include "../Utils.h"

Mesh Line::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

	glm::vec3 axis = getParam<Float3Field>("Axis")->toVec3();
	int divisions = getParam<IntField>("Divisions")->getValue();

	return createLine(axis, divisions);
}

Mesh Line::createLine(glm::vec3 axis, int divisions)
{
    return Mesh();
}