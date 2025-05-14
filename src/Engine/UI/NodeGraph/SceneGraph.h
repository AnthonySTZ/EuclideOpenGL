#pragma once

#include "../../Core/Nodes/Scene.h"
#include "../../Core/Nodes/Node.h"
#include "NodeItem.h"

#include <vector>

class SceneGraph {

public:

	SceneGraph() = default;

	void addNode(NodeItem node);
	void drawNodes();

	
private:
	Scene scene;
	std::vector<NodeItem> nodeItems;

	NodeItem* nodeClicked = nullptr;
	bool nodeMoving = false;
	float moveThreshold = 1.0;

};