#include "Null.h"

Mesh Null::processOutput(uint32_t index)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();

    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex());

    return inputMesh;
}
