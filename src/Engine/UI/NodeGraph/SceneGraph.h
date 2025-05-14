#pragma once

#include "../../Core/Nodes/Scene.h"
#include "NodeItem.h"

class SceneGraph {

public:

	SceneGraph() = default;

	void addNode(NodeItem nodeItem);

private:
	Scene scene;

	std::vector<NodeItem> nodeItems;


};