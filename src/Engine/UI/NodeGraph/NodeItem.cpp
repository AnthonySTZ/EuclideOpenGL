#include "NodeItem.h"

#include <iostream>

void NodeItem::draw()
{
	drawNodeRect();
	drawNodeIO();
}

void NodeItem::drawNodeRect() {

	ImVec2 nodeEnd = nodePos + nodeSize;
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	ImVec4 col = isRender ? nodeRenderColor : nodeColor;

	drawList->AddRectFilled(nodePos, nodeEnd, isHovered() ? vec4ToColor(col * 0.8f) : vec4ToColor(col), 4.0f);
	drawList->AddRect(nodePos, nodeEnd, isSelected ? vec4ToColor(outlineSelectedColor) : IM_COL32(200, 200, 200, 255), 4.0f, 0, 2.0f);

	ImVec2 textSize = ImGui::CalcTextSize(node->getName().c_str());
	ImVec2 textPos = nodePos;
	textPos.x += nodeSize.x * 0.5f - textSize.x * 0.5f;
	textPos.y += nodeSize.y * 0.5f - textSize.y * 0.5f;
	drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), node->getName().c_str());
}

void NodeItem::drawNodeIO() {

	for (auto& nodeIo : nodeIOs) {
		nodeIo.drawAt(nodePos);
	}

}

void NodeItem::createIOs() {

	float width = nodeSize.x - ioPadding * 2 - ioRadius * 0.5f;

	float inputDelta = width / node->getInputsNb();
	ImVec2 inputOffset = ImVec2(0.0, - ioRadius * 1.5f);

	nodeIOs.reserve(node->getInputsNb() + node->getOutputsNb());
	for (int i = 0; i < node->getInputsNb(); i++) {
		float xOffset = 0.5f * inputDelta + i * inputDelta;
		inputOffset.x = xOffset + ioPadding;
		NodeIO nodeIo;
		nodeIo.type = INPUT;
		nodeIo.index = i;
		nodeIo.offset = inputOffset;
		nodeIo.radius = ioRadius;
		nodeIOs.push_back(nodeIo);
	}

	float outputDelta = width / node->getOutputsNb();
	ImVec2 outputOffset = ImVec2(0.0, nodeSize.y + ioRadius * 1.5f);

	for (int i = 0; i < node->getOutputsNb(); i++) {
		float xOffset = 0.5f * outputDelta + i * outputDelta;
		outputOffset.x = xOffset + ioPadding;
		NodeIO nodeIo;
		nodeIo.type = OUTPUT;
		nodeIo.index = i;
		nodeIo.offset = outputOffset;
		nodeIo.radius = ioRadius;
		nodeIOs.push_back(nodeIo);
	}

}

void NodeItem::NodeIO::drawAt(ImVec2 pos) const
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 ioPos = pos + offset;
	drawList->AddCircleFilled(ioPos, radius, IM_COL32(170, 170, 170, 255));
	drawList->AddCircle(ioPos, radius, IM_COL32(200, 200, 200, 255));
}

bool NodeItem::isHovered() const {

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 nodeEnd = nodePos + nodeSize;

	return io.MousePos.x >= nodePos.x && io.MousePos.x <= nodeEnd.x &&
		io.MousePos.y >= nodePos.y && io.MousePos.y <= nodeEnd.y;
}

NodeItem::NodeIO* NodeItem::getIOUnderMouse() const {
	
	float threshold = 5.0f;

	ImGuiIO& io = ImGui::GetIO();
	for (auto &nodeIo : nodeIOs) {
		ImVec2 center = nodePos + nodeIo.offset;
		ImVec2 delta = io.MousePos - center;
		float dist2 = delta.x * delta.x + delta.y * delta.y;

		if (dist2 <= (nodeIo.radius * nodeIo.radius) + threshold) {
			return const_cast<NodeIO*>(&nodeIo);			
		}

	}

	return nullptr;
}

bool NodeItem::isClicked(ImGuiMouseButton mouseButton) const {
	return isHovered() && ImGui::IsMouseClicked(mouseButton);
}

