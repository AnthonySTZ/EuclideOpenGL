#include "NodeConnectionLine.h"

#include <iostream>

NodeConnectionLine::NodeConnectionLine(std::shared_ptr<NodeItem> node_1, NodeItem::NodeIO* nodeIO_1, std::shared_ptr<NodeItem> node_2, NodeItem::NodeIO* nodeIO_2)
{
	if (nodeIO_1->type == NodeItem::OUTPUT) {
		inputNode = node_1;
		inputIO = nodeIO_1;
		outputNode = node_2;
		outputIO = nodeIO_2;
	}
	else {
		inputNode = node_2;
		inputIO = nodeIO_2;
		outputNode = node_1;
		outputIO = nodeIO_1;
	}
	rebuildConnection();
}

void NodeConnectionLine::rebuildConnection() {
	outputNode->getNode()->setInput(outputIO->index, inputNode->getNode(), inputIO->index);
}

void NodeConnectionLine::draw() {

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 ioInputPos = inputNode->getPosition() + inputIO->offset;
	ImVec2 ioOutputPos = outputNode->getPosition() + outputIO->offset;
	drawList->AddLine(ioInputPos, ioOutputPos, IM_COL32(170, 170, 170, 255), 1.5f);

}

bool NodeConnectionLine::ccw(ImVec2 A, ImVec2 B, ImVec2 C) {
	return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x);
}

bool NodeConnectionLine::intersect(ImVec2 A, ImVec2 B, ImVec2 C, ImVec2 D) {
	return ccw(A, C, D) != ccw(B, C, D) and ccw(A, B, C) != ccw(A, B, D);
}

bool NodeConnectionLine::intersectWithLine(ImVec2 lineStart, ImVec2 lineEnd)
{
	ImVec2 startPos = inputNode->getPosition() + inputIO->offset;
	ImVec2 endPos = outputNode->getPosition() + outputIO->offset;

	return intersect(startPos, endPos, lineStart, lineEnd);
}

void NodeConnectionLine::deleteConnection() {
	outputNode->getNode()->deleteInputConnection(outputIO->index);
}