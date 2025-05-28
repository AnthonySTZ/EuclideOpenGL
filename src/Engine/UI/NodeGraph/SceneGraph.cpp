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
	ImGuiIO& io = ImGui::GetIO();

	bool hasClickedIO = false;
	shouldUpdate = false;

	if (ImGui::IsKeyPressed(ImGuiKey_Delete) && nodeSelected != nullptr ) {
		deleteSelectedNode();
	}

	for (auto &nodeItem : nodeItems) {
		nodeItem->draw();
	}

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		for (auto& nodeItem : nodeItems) {
			if (nodeItem->isHovered()) {
				nodeClicked = nodeItem;
				continue;
			}

			NodeItem::NodeIO* tmpNodeIO = nodeItem->getIOUnderMouse();
			if (tmpNodeIO != nullptr) {
				hasClickedIO = true;
				handleIOClicked(nodeItem, tmpNodeIO);
				continue;
			}
		}
	}

	if (ImGui::IsKeyDown(ImGuiKey_Y)) {
		cutConnection();
	}

	if (ImGui::IsKeyReleased(ImGuiKey_Y)) {
		cuttingLines.clear();
		isCutting = false;
	}

	for (auto& line : cuttingLines) {
		line.draw();
	}

	for (auto& conn : nodeConnections) {
		conn->draw();
	}

	
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

		// Click on the graph to cancel current drawing conection
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

void SceneGraph::deleteSelectedNode() {
	for (auto& conn : nodeConnections) {
		for (size_t i = 0; i < nodeConnections.size(); i++) {
			if (nodeConnections[i]->isConnectedTo(nodeSelected)) {
				nodeConnections[i]->deleteConnection();
				nodeConnections.erase(nodeConnections.begin() + i);
			}
		}
	}
	nodeSelected->deleteNode();
	nodeItems.erase(
		std::remove(nodeItems.begin(), nodeItems.end(), nodeSelected), nodeItems.end()
	);
	scene.deleteNode(nodeSelected->getNode()->getName().c_str());
	renderNode = nullptr;
	nodeSelected = nullptr;
	shouldUpdate = true;
}

void SceneGraph::cutConnection() {
	ImGuiIO& io = ImGui::GetIO();

	isCutting = true;
	if (io.MousePosPrev != io.MousePos) {
		cuttingLines.push_back(CuttingLine(io.MousePosPrev, io.MousePos));
		for (size_t i = 0; i < nodeConnections.size(); i++) {
			if (nodeConnections[i]->intersectWithLine(io.MousePosPrev, io.MousePos)) {
				nodeConnections[i]->deleteConnection();
				nodeConnections.erase(nodeConnections.begin() + i);
				shouldUpdate = true;
				break;
			}
		}
	}
}

void SceneGraph::handleIOClicked(std::shared_ptr<NodeItem> nodeItem, NodeItem::NodeIO* io) {
	if (ioClicked == nullptr) {
		ioClicked = io;
		currentIoNode = nodeItem;
		return;
	}

	if ((io->type != ioClicked->type) && (nodeItem->getNode()->getName() != currentIoNode->getNode()->getName())) {

		std::shared_ptr<NodeConnectionLine> conn = std::make_shared<NodeConnectionLine>(
			nodeItem,
			io,
			currentIoNode,
			ioClicked
		);

		for (size_t i = 0; i < nodeConnections.size(); i++) {
			if (nodeConnections[i]->getOutputNode() == conn->getOutputNode() && nodeConnections[i]->getOutputIO() == conn->getOutputIO()) {
				nodeConnections[i]->deleteConnection();
				nodeConnections[i] = nodeConnections.back();
				nodeConnections.pop_back();
				break;
			}
		}
		conn->rebuildConnection();
		nodeConnections.push_back(conn);

		ioClicked = nullptr;
		currentIoNode = nullptr;
		shouldUpdate = true;

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
