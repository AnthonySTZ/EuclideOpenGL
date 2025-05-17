#include "NodeConnectionLine.h"

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
	outputNode->getNode()->setInput(outputIO->index, inputNode->getNode(), inputIO->index);
}

void NodeConnectionLine::draw() {

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 ioInputPos = inputNode->getPosition() + inputIO->offset;
	ImVec2 ioOutputPos = outputNode->getPosition() + outputIO->offset;
	drawList->AddLine(ioInputPos, ioOutputPos, IM_COL32(170, 170, 170, 255), 1.5f);

}