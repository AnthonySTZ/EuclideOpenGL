#include "Torus.h"

#include "../Utils.h"

#include <glm/gtc/constants.hpp>

Mesh& Torus::processOutput(uint32_t index, bool *updateDirty)
{

    if (!isDirty()){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    int nRings = getParam<IntField>("nRings")->getValue();
    int ringSubd = getParam<IntField>("ringSubd")->getValue();
    float ringRadius = getParam<FloatField>("ringRadius")->getValue();
    float torusRadius = getParam<FloatField>("torusRadius")->getValue();
    
	Timer timer{ nodeName.c_str() };
    cachedMesh = createTorus(nRings, ringSubd, ringRadius, torusRadius);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

	return cachedMesh;
}

Mesh Torus::createTorus(int nRings, int ringSubd, float ringRadius, float torusRadius)
{
    float phi = 0.0f;
    float dp = (2*glm::pi<float>()) / ringSubd;

    float theta = 0.0f;
    float dt = (2*glm::pi<float>()) / nRings;

    Mesh::Builder builder;

    for (int stack=0; stack<nRings; stack++){

        theta = dt * stack;
        for (int slice=0; slice < ringSubd; slice++){

            phi = dp * slice;
            glm::vec3 position {
                glm::cos(theta) * (torusRadius + glm::cos(phi) * ringRadius),
                glm::sin(phi) * ringRadius,
                -glm::sin(theta) * (torusRadius + glm::cos(phi) * ringRadius)
            };
            builder.addPoint(position);

        }

    }

    for (int stack=0; stack<nRings-1; stack++){
        for (int slice=0; slice < ringSubd; slice++){

            uint32_t pt1 = stack * ringSubd + slice;
            uint32_t pt2 = (stack + 1) * ringSubd + slice;
            uint32_t pt3 = stack * ringSubd + (slice + 1) % ringSubd;
            uint32_t pt4 = (stack + 1) * ringSubd + (slice + 1) % ringSubd;
            builder.addFace({pt1, pt2, pt4, pt3});
        }
    } 

    for (int slice = 0; slice < ringSubd; slice++) { // Connect the end rings
        uint32_t pt1 = (nRings - 1) * ringSubd + slice;
        uint32_t pt2 = slice;
        uint32_t pt3 = (nRings - 1) * ringSubd + (slice + 1) % ringSubd;
        uint32_t pt4 = (slice + 1) % ringSubd;

        builder.addFace({pt1, pt2, pt4, pt3});
    }

    return Mesh{builder};
}