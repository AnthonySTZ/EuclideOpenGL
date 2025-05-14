#include "SceneGraph.h"

#include <iostream>


void SceneGraph::addNode(NodeItem nodeItem)
{
	std::shared_ptr<NodeItem> nodeItemPtr = std::make_shared<NodeItem>(nodeItem);
	nodeItems.push_back(nodeItemPtr);
	scene.addNode(nodeItemPtr->getNode());

}

void SceneGraph::drawNodes()
{

	for (auto &nodeItem : nodeItems) {
		nodeItem->draw();

		if (nodeItem->isClicked(ImGuiMouseButton_Left)) {

			nodeClicked = nodeItem;
			std::cout << nodeItem->getNode()->getName() << " clicked!\n";

		}

	}

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 dragDelta = io.MouseDelta;
	if (nodeMoving) {

		if (nodeClicked != nullptr) {
			nodeClicked->moveBy(dragDelta);
		}

	}
	else if (nodeClicked) {

		if (abs(dragDelta.x + dragDelta.y) >= moveThreshold) {
			nodeMoving = true;
		}

	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left) && nodeClicked != nullptr) {

		if (!nodeMoving) {

			std::cout << "Deselect " << nodeSelected.get() << "\n";
			if (nodeSelected != nullptr) nodeSelected->setSelected(false);
			nodeSelected = nodeClicked;
			std::cout << "Select " << nodeSelected.get() << "\n";
			nodeClicked->setSelected(true);

		}

		nodeClicked = nullptr;
		nodeMoving = false;

	}

	if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Middle) && nodeClicked == nullptr) {

		for (auto& nodeItem : nodeItems) {
			nodeItem->moveBy(dragDelta);
		}

	}

}
