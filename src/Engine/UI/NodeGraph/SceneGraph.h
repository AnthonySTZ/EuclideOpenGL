#pragma once

#include "../../Core/Nodes/Scene.h"
#include "../../Core/Nodes/Node.h"
#include "NodeItem.h"

#include <vector>

class SceneGraph {

public:

	SceneGraph() = default;

	void addNode(NodeItem node);
	void drawNodes() { 
		for (auto& nodeItem : nodeItems) {
			nodeItem.draw();
		}
	};

	
private:
	Scene scene;
	std::vector<NodeItem> nodeItems;


};