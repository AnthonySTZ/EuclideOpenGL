#include "PointGenerate.h"

#include "../Utils.h"

Mesh& PointGenerate::processOutput(uint32_t index, bool *updateDirty)
{	
	
	if (!isDirty()){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 
	
	int nPoints = getParam<IntField>("nPoints")->getValue();
	glm::vec3 pos = getParam<Float3Field>("Position")->toVec3();
	
	Timer timer{ nodeName.c_str() };

	cachedMesh = generatePoints(nPoints, pos);

	if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

Mesh PointGenerate::generatePoints(int nb, glm::vec3 position)
{
	Mesh::Builder builder;

	builder.points.reserve(nb);
	for (int i = 0; i < nb; i++){
		builder.addPoint(position);
	}


    return Mesh{builder};
}
