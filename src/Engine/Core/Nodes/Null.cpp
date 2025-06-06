#include "Null.h"

Mesh Null::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();

    bool isInputDirty = false;
    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (updateDirty != nullptr) *updateDirty = isInputDirty;

    return inputMesh;
}
