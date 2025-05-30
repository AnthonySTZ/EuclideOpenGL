#include "Cylinder.h"

#include "../Utils.h"

#include <glm/gtc/constants.hpp>

Mesh Cylinder::processOutput(uint32_t index)
{
	Timer timer{ nodeName.c_str() };

	float radiusTop = getParam<FloatField>("RadiusTop")->getValue();
	float radiusBottom = getParam<FloatField>("RadiusBottom")->getValue();
	float height = getParam<FloatField>("Height")->getValue();
	int divisions = getParam<IntField>("Divisions")->getValue();
	glm::vec3 translate = getParam<Float3Field>("Translate")->toVec3();

	return createCylinder(translate, glm::vec2(radiusTop, radiusBottom), height, divisions);
}

Mesh Cylinder::createCylinder(glm::vec3 position, glm::vec2 radius, float height, int divisions)
{
	if (divisions < 3) return Mesh();

	Mesh::Builder cylBuilder;

	cylBuilder.points.reserve(divisions * 2);

	for (int topDiv = 0; topDiv < divisions; topDiv++) { // Create top circle points

		float angle = ((float)topDiv / (float)divisions) * 2 * glm::pi<float>();

		Point point;
		point.id = topDiv;
		point.position = glm::vec3(
			glm::cos(angle) * radius.x,
			height*0.5f,
			glm::sin(angle) * radius.x);
		point.position += position;
		cylBuilder.points.push_back(point);
	}

	for (int bottomDiv = 0; bottomDiv < divisions; bottomDiv++) { // Create bottom circle points

		// TODO: Try to just duplicate the top part to prevent redo divisions

		float angle = ((float)bottomDiv / (float)divisions) * 2 * glm::pi<float>();

		Point point;
		point.id = divisions + bottomDiv;
		point.position = glm::vec3(
			glm::cos(angle) * radius.y,
			- height * 0.5f,
			glm::sin(angle) * radius.y);
		point.position += position;
		cylBuilder.points.push_back(point);
	}

	cylBuilder.faces.reserve(divisions);

	for (int i = 0; i < divisions; i++) {

		uint32_t topFirstPt = i;
		uint32_t topSecondPt = (i + 1) % divisions;

		uint32_t bottomFirstPt = topFirstPt + divisions;
		uint32_t bottomSecondPt = topSecondPt + divisions;

		Face face;
		face.pointIds = { topFirstPt , topSecondPt , bottomSecondPt ,  bottomFirstPt };
		cylBuilder.faces.push_back(face);

	}


    return Mesh{cylBuilder};
}
