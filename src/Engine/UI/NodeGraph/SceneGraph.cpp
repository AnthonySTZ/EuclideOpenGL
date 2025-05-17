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
	bool hasClickedIO = false;
	shouldUpdate = false;
	for (auto &nodeItem : nodeItems) {
		nodeItem->draw();

		if (nodeItem->isClicked(ImGuiMouseButton_Left)) nodeClicked = nodeItem;

		NodeItem::NodeIO* tmpNodeIO = nodeItem->IOClicked(ImGuiMouseButton_Left);
		if (tmpNodeIO == nullptr) continue;
		
		hasClickedIO = true;
		if (ioClicked == nullptr) {
			ioClicked = tmpNodeIO;
			currentIoNode = nodeItem;
			continue;
		}
		
		// CREATE CONNECTION
		if ((tmpNodeIO->type != ioClicked->type) && (nodeItem->getNode()->getName() != currentIoNode->getNode()->getName())) {

			std::shared_ptr<NodeConnectionLine> conn = std::make_shared<NodeConnectionLine>(
				nodeItem,
				tmpNodeIO,
				currentIoNode,
				ioClicked
			);
			nodeConnections.push_back(conn);

			ioClicked = nullptr;
			currentIoNode = nullptr;			
			shouldUpdate = true;
				
		}

	}

	for (auto& conn : nodeConnections) {
		conn->draw();
	}

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 dragDelta = io.MouseDelta;
	if (nodeMoving) {

		if (nodeClicked != nullptr) {
			nodeClicked->moveBy(dragDelta);
		}

	}

	if (nodeClicked) {

		if (abs(dragDelta.x + dragDelta.y) >= moveThreshold) {
			nodeMoving = true;
		}

	}

	if (currentIoNode != nullptr) {
		drawCurrentConnectionLine();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !hasClickedIO) {
			currentIoNode = nullptr;
			ioClicked = nullptr;
		}
	}	

	if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left) && nodeClicked != nullptr) {

		if (!nodeMoving) {

			if (nodeSelected != nullptr) nodeSelected->setSelected(false);

			nodeSelected = nodeClicked;
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

void SceneGraph::drawCurrentConnectionLine() {

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 ioPos = currentIoNode->getPosition() + ioClicked->offset;

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddLine(io.MousePos, ioPos, IM_COL32(255, 255, 255, 255));

}

void SceneGraph::setSelectedNodeRender()
{
	for (auto& nodeItem : nodeItems) {

		nodeItem->setRenderState(false);

	}

	renderNode = nullptr;
	if (nodeSelected != nullptr) {
		nodeSelected->setRenderState(true);
		renderNode = nodeSelected;
	}
}
