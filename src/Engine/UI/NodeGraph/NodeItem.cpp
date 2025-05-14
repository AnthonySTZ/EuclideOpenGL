#include "NodeItem.h"

#include <iostream>

void NodeItem::draw()
{
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 nodeEnd = nodePos + nodeSize;

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	if (isClicked(ImGuiMouseButton_Left)) std::cout << node->getName() << " clicked\n";

	drawList->AddRectFilled(nodePos, nodeEnd, isHovered() ? nodeColor * 0.8 : nodeColor, 4.0f);
	drawList->AddRect(nodePos, nodeEnd, IM_COL32(200, 200, 200, 255), 4.0f);

	drawList->AddText(nodePos + ImVec2(25, 15), IM_COL32(255, 255, 255, 255), node->getName().c_str());

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
