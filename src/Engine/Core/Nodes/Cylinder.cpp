#include "Cylinder.h"

#include "../Utils.h"

#include <glm/gtc/constants.hpp>

#include <numeric>

Mesh Cylinder::processOutput(uint32_t index, bool *updateDirty)
{
	Timer timer{ nodeName.c_str() };

	float radiusTop = getParam<FloatField>("RadiusTop")->getValue();
	float radiusBottom = getParam<FloatField>("RadiusBottom")->getValue();
	float height = getParam<FloatField>("Height")->getValue();
	int divisions = getParam<IntField>("Divisions")->getValue();
	int capped = getParam<BooleanField>("Capped")->getValue();
	glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

	return createCylinder(translate, glm::vec2(radiusTop, radiusBottom), height, divisions, capped);
}

Mesh Cylinder::createCylinder(glm::vec3 position, glm::vec2 radius, float height, int divisions, bool capped)
{
	if (divisions < 3) return Mesh();

	Mesh::Builder cylBuilder;
	cylBuilder.points.resize(divisions * 2);
	cylBuilder.faces.reserve(divisions);

	const float angleStep = glm::two_pi<float>() / static_cast<float>(divisions);


	for (uint32_t div = 0; div < divisions; div++) { // Create circles points

		float angle = div * angleStep;
		float cosAngle = glm::cos(angle);
		float sinAngle = glm::sin(angle);

		cylBuilder.points[div].id = div;
		cylBuilder.points[div].position = 
			glm::vec3(cosAngle * radius.x,
				height * 0.5f,
				sinAngle * radius.x) + position;

		cylBuilder.points[div + divisions].id = div + divisions;
		cylBuilder.points[div + divisions].position =
			glm::vec3(cosAngle * radius.y,
				height * -0.5f,
				sinAngle * radius.y) + position;

	}

	for (int i = 0; i < divisions; i++) {

		uint32_t topFirstPt = i;
		uint32_t topSecondPt = (i + 1) % divisions;

		uint32_t bottomFirstPt = topFirstPt + divisions;
		uint32_t bottomSecondPt = topSecondPt + divisions;

		cylBuilder.faces.emplace_back(Face{
			{ topFirstPt, topSecondPt, bottomSecondPt, bottomFirstPt }
		});

	}

	if (capped) {
		std::vector<uint32_t> topIds(divisions);
		std::vector<uint32_t> bottomIds(divisions);
		for (uint32_t i = 0; i < divisions; i++) {
			topIds[i] = divisions - i - 1; // ClockWise for good normal
			bottomIds[i] = i + divisions;
		}

		cylBuilder.faces.emplace_back(Face{ topIds });
		cylBuilder.faces.emplace_back(Face{ bottomIds });
	}

    return Mesh{cylBuilder};
}
