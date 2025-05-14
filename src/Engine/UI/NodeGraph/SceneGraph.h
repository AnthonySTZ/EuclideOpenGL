#pragma once

#include "../../Core/Nodes/Scene.h"
#include "../../Core/Nodes/Node.h"
#include "NodeItem.h"

#include <vector>

class SceneGraph {

public:

	SceneGraph() = default;

	void addNode(NodeItem node);

	Scene scene;
	std::vector<NodeItem> nodeItems;
private:



};