#include "Line.h"

#include "../Utils.h"

Mesh Line::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

	glm::vec3 axis = getParam<Float3Field>("Axis")->toVec3();
	int divisions = getParam<IntField>("Divisions")->getValue();
	float length = getParam<FloatField>("Length")->getValue();
	

	return createLine(axis, divisions, length);
}

Mesh Line::createLine(glm::vec3 axis, int divisions, float length)
{

	if (divisions<2) return Mesh();

	Mesh::Builder builder;
	builder.points.reserve(divisions);
	builder.faces.reserve(divisions - 1);

	glm::vec3 nDir = glm::normalize(axis);
	float stepSize = length / (float)(divisions - 1);

	for(uint32_t i=0; i<divisions; i++){
		Point point {i, nDir * (stepSize * static_cast<float>(i))};
		builder.points.push_back(point);
	}


    return Mesh{builder};
}