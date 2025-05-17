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
	void handleIOClicked(std::shared_ptr<NodeItem> nodeItem, NodeItem::NodeIO* io);
	void drawCurrentConnectionLine();
	void setSelectedNodeRender();


	std::shared_ptr<NodeItem> getSelectedNode() const { return nodeSelected; };
	std::shared_ptr<NodeItem> getRenderNode() const { return renderNode; };
	bool shouldUpdateRender() const { return shouldUpdate; };

	
private:
	Scene scene;
	std::vector<std::shared_ptr<NodeItem>> nodeItems;
	std::vector<std::shared_ptr<NodeConnectionLine>> nodeConnections;

	std::shared_ptr<NodeItem> nodeClicked = nullptr;
	std::shared_ptr<NodeItem> nodeSelected = nullptr;
	std::shared_ptr<NodeItem> renderNode = nullptr;
	NodeItem::NodeIO* ioClicked = nullptr;
	std::shared_ptr<NodeItem> currentIoNode = nullptr;

	bool nodeMoving = false;
	float moveThreshold = 1.0;

	bool shouldUpdate = false;

};