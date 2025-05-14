#include "SceneGraph.h"

#include <iostream>

void SceneGraph::addNode(NodeItem nodeItem)
{
	nodeItems.push_back(nodeItem);
	scene.addNode(nodeItem.getNode());

}

void SceneGraph::drawNodes()
{
	ImGuiIO& io = ImGui::GetIO();

	for (auto& nodeItem : nodeItems) {
		nodeItem.draw();

		if (nodeItem.isClicked(ImGuiMouseButton_Left)) {

			nodeClicked = &nodeItem;
			std::cout << nodeItem.getNode()->getName() << " clicked!\n";

		}

	}

	ImVec2 dragDelta = ImGui::GetIO().MouseDelta;
	if (nodeMoving) {

		nodeClicked->moveBy(dragDelta);

	}
	else if (nodeClicked) {

		if (abs(dragDelta.x + dragDelta.y) >= moveThreshold) {
			nodeMoving = true;
		}

	}

	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && nodeClicked != nullptr) {

		nodeClicked = nullptr;
		nodeMoving = false;

	}

}
