#include "SceneGraph.h"

#include <iostream>

void SceneGraph::addNode(NodeItem nodeItem)
{
	nodeItems.push_back(nodeItem);
	scene.addNode(nodeItem.getNode());

}

void SceneGraph::drawNodes()
{

	for (auto& nodeItem : nodeItems) {
		nodeItem.draw();

		if (nodeItem.isClicked(ImGuiMouseButton_Left)) {

			nodeClicked = &nodeItem;
			std::cout << nodeItem.getNode()->getName() << " clicked!\n";

		}

	}

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 dragDelta = io.MouseDelta;
	if (nodeMoving) {

		nodeClicked->moveBy(dragDelta);

	}
	else if (nodeClicked) {

		if (abs(dragDelta.x + dragDelta.y) >= moveThreshold) {
			nodeMoving = true;
		}

	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left) && nodeClicked != nullptr) {

		nodeClicked = nullptr;
		nodeMoving = false;

	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Middle) && nodeClicked == nullptr) {

		for (auto& nodeItem : nodeItems) {
			nodeItem.moveBy(dragDelta);
		}

	}

}
