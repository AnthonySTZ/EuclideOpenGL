#include "Null.h"

Mesh& Null::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()){
        cachedMesh = Mesh();
        return cachedMesh;
    }

    bool isInputDirty = false;
    cachedMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (updateDirty != nullptr) *updateDirty = isInputDirty;

    return cachedMesh;
}
