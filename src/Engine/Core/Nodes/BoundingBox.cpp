#include "BoundingBox.h"

#include "Cube.h"

Mesh BoundingBox::processOutput(uint32_t index, bool *updateDirty) {

    auto it_0 = inputs.find(0);
    if (it_0 == inputs.end()) {
        return Mesh();
    }

    bool isInputDirty = false;
    Mesh inputMesh_0 = it_0->second->getInputNode()->processOutput(it_0->second->getInputIndex(), &isInputDirty);

    if (!isInputDirty && !isDirty())
    {
        if (updateDirty != nullptr) *updateDirty = false;
        return cachedMesh;
    } 

    BBox bbox = computeBoundingBox(inputMesh_0);

    glm::vec3 position = glm::vec3(
        (bbox.max.x + bbox.min.x) * 0.5f,
        (bbox.max.y + bbox.min.y) * 0.5f,
        (bbox.max.z + bbox.min.z) * 0.5f
    );

    glm::vec3 size = glm::vec3(
        (bbox.max.x - bbox.min.x),
        (bbox.max.y - bbox.min.y),
        (bbox.max.z - bbox.min.z)
    );;

    if (updateDirty != nullptr) *updateDirty = true;
    dirty = false;

    cachedMesh = Cube::createCube(position, size);

    return cachedMesh;
}

BoundingBox::BBox BoundingBox::computeBoundingBox(Mesh& mesh)
{
    BBox bbox;
    if (mesh.points.size() == 0) return bbox;

    // Init bbox
    bbox.min = mesh.points[0].position;
    bbox.max = mesh.points[0].position;

    for (auto& point : mesh.points) {

        if (point.position.x < bbox.min.x) bbox.min.x = point.position.x;
        if (point.position.y < bbox.min.y) bbox.min.y = point.position.y;
        if (point.position.z < bbox.min.z) bbox.min.z = point.position.z;

        if (point.position.x > bbox.max.x) bbox.max.x = point.position.x;
        if (point.position.y > bbox.max.y) bbox.max.y = point.position.y;
        if (point.position.z > bbox.max.z) bbox.max.z = point.position.z;
    }

    return bbox;
}
