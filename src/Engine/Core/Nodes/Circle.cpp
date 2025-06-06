#include "Circle.h"

#include "../Utils.h"

#include <glm/gtc/constants.hpp>

Mesh Circle::processOutput(uint32_t index, bool *updateDirty)
{
	Timer timer{ nodeName.c_str() };

	if (!isDirty()){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

	int divisions = getParam<IntField>("Divisions")->getValue();
	float radius = getParam<FloatField>("Radius")->getValue();
	
	if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

	cachedMesh = createCircle(divisions, radius);

	return cachedMesh;
}

Mesh Circle::createCircle(int divisions, float radius)
{
    if (divisions < 3) return Mesh();

    Mesh::Builder builder;
    builder.points.reserve(divisions);

    const float angleStep = glm::two_pi<float>() / static_cast<float>(divisions);

    for (uint32_t div = 0; div < divisions; div++) { // Create circles points

		float angle = div * angleStep;
		float cosAngle = glm::cos(angle);
		float sinAngle = glm::sin(angle);
		glm::vec3 position = glm::vec3(cosAngle * radius, 0.0f, sinAngle * radius);

        builder.points.emplace_back(Point{div, position});
	}

    for(uint32_t i=0; i<divisions; i++){ // Create faces
		builder.faces.emplace_back(Face{ {i, (i+1) % divisions} });
	}

    return Mesh{builder};
}