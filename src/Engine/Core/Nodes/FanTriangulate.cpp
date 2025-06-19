#include "FanTriangulate.h"

#include "../Utils.h"
#include <algorithm>

Mesh& FanTriangulate::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()){
        cachedMesh = Mesh();
        return cachedMesh;
    }

    bool isInputDirty = false;
    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (!isDirty() && !isInputDirty){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    cachedMesh = fanTriangulate(inputMesh);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

Mesh FanTriangulate::fanTriangulate(Mesh& mesh)
{

    return Mesh();

}
