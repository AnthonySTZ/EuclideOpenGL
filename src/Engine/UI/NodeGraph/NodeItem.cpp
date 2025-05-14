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

	drawList->AddRectFilled(nodePos, nodeEnd, isHovered() ? nodeColor * 0.8f : nodeColor, 4.0f);
	drawList->AddRect(nodePos, nodeEnd, IM_COL32(200, 200, 200, 255), 4.0f);

	ImVec2 textSize = ImGui::CalcTextSize(node->getName().c_str());
	ImVec2 textPos = nodePos;
	textPos.x += nodeSize.x * 0.5f - textSize.x * 0.5f;
	textPos.y += nodeSize.y * 0.5f - textSize.y * 0.5f;
	drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), node->getName().c_str());
}

void NodeItem::drawNodeIO() {

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	float radius = 6.0f;
	float padding = 5.0f;
	float width = nodeSize.x - padding * 2 - radius * 0.5f;

	float inputDelta = width / node->getInputsNb();
	ImVec2 inputPos = ImVec2(0.0, nodePos.y - radius * 1.5f);

	for (int i = 0; i < node->getInputsNb(); i++) {
		float xOffset = 0.5f * inputDelta + i * inputDelta;
		inputPos.x = nodePos.x + xOffset + padding;
		drawList->AddCircleFilled(inputPos, radius, IM_COL32(170, 170, 170, 255));
		drawList->AddCircle(inputPos, radius, IM_COL32(200, 200, 200, 255));
	}

	float outputDelta = width / node->getOutputsNb();
	ImVec2 outputPos = ImVec2(0.0, nodePos.y + nodeSize.y + radius * 1.5f);

	for (int i = 0; i < node->getOutputsNb(); i++) {
		float xOffset = 0.5f * outputDelta + i * outputDelta;
		outputPos.x = nodePos.x + xOffset + padding;
		drawList->AddCircleFilled(outputPos, radius, IM_COL32(170, 170, 170, 255));
		drawList->AddCircle(outputPos, radius, IM_COL32(200, 200, 200, 255));
	}

}

bool NodeItem::isHovered() const {

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 nodeEnd = nodePos + nodeSize;

	return io.MousePos.x >= nodePos.x && io.MousePos.x <= nodeEnd.x &&
		io.MousePos.y >= nodePos.y && io.MousePos.y <= nodeEnd.y;
}

bool NodeItem::isClicked(ImGuiMouseButton mouseButton) const {
	return isHovered() && ImGui::IsMouseClicked(mouseButton);
}
