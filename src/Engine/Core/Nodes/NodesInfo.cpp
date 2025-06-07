#include "NodesInfo.h"

#include "ImportObj.h"
#include "Cube.h"
#include "UVSphere.h"
#include "QuadSphere.h"
#include "Grid.h"
#include "Cylinder.h"
#include "Torus.h"
#include "Line.h"
#include "Circle.h"
#include "Transform.h"
#include "Duplicate.h"
#include "Subdivide.h"
#include "SmoothNormals.h"
#include "HardenNormals.h"
#include "Merge.h"
#include "CopyToPoints.h"
#include "BoundingBox.h"
#include "VisualizeNormals.h"
#include "Null.h"


static const std::map<const char*, std::vector<NodeMenuItem>> nodeMenuItems = {
    {"Import",
        {
            {"ImportObj", []() { return std::make_shared<ImportObj>(); }}
        }
    },
    {"Primitive", 
        {
            {"Cube", []() { return std::make_shared<Cube>(); }}, 
            {"UVSphere", []() { return std::make_shared<UVSphere>(); }}, 
            {"QuadSphere", []() { return std::make_shared<QuadSphere>(); }}, 
            {"Grid", []() { return std::make_shared<Grid>(); }},
            {"Cylinder", []() { return std::make_shared<Cylinder>(); }},
            {"Torus", []() { return std::make_shared<Torus>(); }},
            {"Line", []() { return std::make_shared<Line>(); }},
            {"Circle", []() { return std::make_shared<Circle>(); }}
        }
    },
    {"Geometry",
        {
            {"Transform", []() { return std::make_shared<Transform>(); }},
            {"Subdivide", []() { return std::make_shared<Subdivide>(); }},
            {"Merge", []() { return std::make_shared<Merge>(); }},
            {"SmoothNormals", []() { return std::make_shared<SmoothNormals>(); }},
            {"HardenNormals", []() { return std::make_shared<HardenNormals>(); }},
            {"BoundingBox", []() { return std::make_shared<BoundingBox>(); }}
        }
    },
    {"Copying",
        {
            {"CopyToPoints", []() { return std::make_shared<CopyToPoints>(); }},
            {"Duplicate", []() { return std::make_shared<Duplicate>(); }}
        }
    },
    {"Utility",
        {
            {"Null", []() { return std::make_shared<Null>(); }},
            {"VisualizeNormals", []() { return std::make_shared<VisualizeNormals>(); }}
        }
    }
};

// Provide access to the internal static vector
const std::map<const char*, std::vector<NodeMenuItem>>& NodesInfo::getMenuItems() {
    return nodeMenuItems;
}