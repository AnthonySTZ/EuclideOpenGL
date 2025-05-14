#pragma once

#include "../../Core/Nodes/Scene.h"
#include "NodeItem.h"

class SceneGraph {

public:

	SceneGraph() = default;

private:
	Scene scene;

	std::vector<NodeItem> nodeItems;


};