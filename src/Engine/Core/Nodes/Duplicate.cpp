#include "Duplicate.h"

#include "../Utils.h"
#include <algorithm>

#include "Transform.h"
#include "Merge.h"

glm::vec3 vec3Pow(glm::vec3 vec, float power){
    return glm::vec3(glm::pow(vec.x, power), glm::pow(vec.y, power), glm::pow(vec.z, power));    
}

Mesh Duplicate::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();

    bool isInputDirty = false;
    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (!isDirty() && !isInputDirty){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    int nCopies = getParam<IntField>("nCopies")->getValue();
    glm::vec3 rotation = getParam<Float3Field>("Rotate")->toVec3();
    glm::vec3 scale = getParam<Float3Field>("Scale")->toVec3();
    glm::vec3 translation = getParam<Float3Field>("Translate")->toVec3();

    if (nCopies < 1) return Mesh();

    Timer timer{ nodeName.c_str() };

    cachedMesh = inputMesh;
    Mesh transformedMesh{};

    for (int i=1; i<nCopies; i++){
        
        transformedMesh = Transform::scaleMesh(inputMesh, vec3Pow(scale, (float)i));
        transformedMesh = Transform::rotateMesh(transformedMesh, rotation * (float)i);
        transformedMesh = Transform::translateMesh(transformedMesh, translation * (float)i);

        cachedMesh = Merge::mergeToMesh(cachedMesh, transformedMesh);

    }

	if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

