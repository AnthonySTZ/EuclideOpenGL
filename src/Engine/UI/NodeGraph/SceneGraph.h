#pragma once

#include "../../Core/Nodes/Scene.h"
#include "../../Core/Nodes/Node.h"
#include "NodeItem.h"
#include "NodeConnectionLine.h"

#include <vector>

class SceneGraph {

public:

	SceneGraph() = default;

	void addNode(NodeItem node);
	void drawNodes();

	
private:
	Scene scene;
	std::vector<std::shared_ptr<NodeItem>> nodeItems;
	std::vector<std::shared_ptr<NodeConnectionLine>> nodeConnections;

	std::shared_ptr<NodeItem> nodeClicked = nullptr;
	std::shared_ptr<NodeItem> nodeSelected = nullptr;
	NodeItem::NodeIO* ioClicked = nullptr;
	std::shared_ptr<NodeItem> currentIoNode = nullptr;

	bool nodeMoving = false;
	float moveThreshold = 1.0;

};