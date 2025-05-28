#include "BoundingBox.h"

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
