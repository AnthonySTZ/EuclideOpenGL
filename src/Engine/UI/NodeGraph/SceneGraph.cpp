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
	for (auto &nodeItem : nodeItems) {
		nodeItem->draw();

		if (nodeItem->isClicked(ImGuiMouseButton_Left)) {

			nodeClicked = nodeItem;
			std::cout << nodeItem->getNode()->getName() << " clicked!\n";

		}

		NodeItem::NodeIO* tmpNodeIO = nodeItem->IOClicked(ImGuiMouseButton_Left);
		if (tmpNodeIO != nullptr) {
			hasClickedIO = true;
			if (ioClicked == nullptr) {
				ioClicked = tmpNodeIO;
				currentIoNode = nodeItem;
			}
			else {
				// CREATE CONNECTION
				if ((tmpNodeIO->type != ioClicked->type) && (nodeItem->getNode()->getName() != currentIoNode->getNode()->getName())) {

					std::shared_ptr<NodeItem> inputNode;
					std::shared_ptr<NodeItem> outputNode;
					NodeItem::NodeIO* inputIO;
					NodeItem::NodeIO* outputIO;

					if (tmpNodeIO->type == NodeItem::OUTPUT) {
						inputNode = nodeItem;
						inputIO = tmpNodeIO;
						outputNode = currentIoNode;
						outputIO = ioClicked;
					}
					else {
						inputNode = currentIoNode;
						inputIO = ioClicked;
						outputNode = nodeItem;
						outputIO = tmpNodeIO;
					}

					std::shared_ptr<NodeConnectionLine> conn = std::make_shared<NodeConnectionLine>(
						inputNode,
						inputIO,
						outputNode,
						outputIO
					);
					nodeConnections.push_back(conn);
					outputNode->getNode()->setInput(outputIO->index, inputNode->getNode(), inputIO->index);

					std::cout << "Create connection between " <<
						currentIoNode->getNode()->getName() << " at index " << ioClicked->index << " and " <<
						nodeItem->getNode()->getName() << " at index " << tmpNodeIO->index << "\n";
					ioClicked = nullptr;
					currentIoNode = nullptr;


				}

				

			}
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
	else if (nodeClicked) {

		if (abs(dragDelta.x + dragDelta.y) >= moveThreshold) {
			nodeMoving = true;
		}

	}

	if (currentIoNode != nullptr) {
		ImGuiIO& io = ImGui::GetIO();
		ImVec2 ioPos = currentIoNode->getPosition() + ioClicked->offset;
		
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		drawList->AddLine(io.MousePos, ioPos, IM_COL32(255, 255, 255, 255));

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !hasClickedIO) {
			currentIoNode = nullptr;
			ioClicked = nullptr;
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
