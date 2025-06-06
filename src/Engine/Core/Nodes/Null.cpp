#include "Null.h"

Mesh Null::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();

    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    return inputMesh;
}
