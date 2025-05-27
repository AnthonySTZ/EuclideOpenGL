#include "NodesInfo.h"

#include "Cube.h"
#include "Grid.h"
#include "Transform.h"
#include "Merge.h"
#include "CopyToPoints.h"
#include "Null.h"


static const std::vector<NodeMenuItem> nodeMenuItems = {
    {"Cube", []() { return std::make_shared<Cube>(); }},
    {"Grid", []() { return std::make_shared<Grid>(); }},
    {"Transform", []() { return std::make_shared<Transform>(); }},
    {"Merge", []() { return std::make_shared<Merge>(); }},
    {"CopyToPoints", []() { return std::make_shared<CopyToPoints>(); }},
    {"Null", []() { return std::make_shared<Null>(); }},
};

// Provide access to the internal static vector
const std::vector<NodeMenuItem>& NodesInfo::getMenuItems() {
    return nodeMenuItems;
}