#include "Torus.h"

#include "../Utils.h"

#include <glm/gtc/constants.hpp>

Mesh Torus::processOutput(uint32_t index, bool *updateDirty)
{

    if (!isDirty()){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    int nRings = getParam<IntField>("nRings")->getValue();
    int ringSubd = getParam<IntField>("ringSubd")->getValue();
    float innerRadius = getParam<FloatField>("innerRadius")->getValue();
    float outerRadius = getParam<FloatField>("outerRadius")->getValue();
    
	Timer timer{ nodeName.c_str() };
    cachedMesh = createTorus(nRings, ringSubd, innerRadius, outerRadius);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

	return cachedMesh;
}

Mesh Torus::createTorus(int nRings, int ringSubd, float innerRadius, float outerRadius)
{
    return Mesh();
}