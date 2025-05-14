#include "NodeItem.h"

#include <iostream>

void NodeItem::draw()
{
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 nodeSize = ImVec2(80, 40);
	ImVec2 nodeEnd = pos + nodeSize;

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	bool nodeHovered = io.MousePos.x >= pos.x && io.MousePos.x <= nodeEnd.x &&
		io.MousePos.y >= pos.y && io.MousePos.y <= nodeEnd.y;
	bool nodeClicked = nodeHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left);
	if (nodeClicked) std::cout << node->getName() << " clicked\n";

	ImU32 nodeColor = nodeHovered ? IM_COL32(200, 150, 80, 255) : IM_COL32(100, 100, 150, 255);
	drawList->AddRectFilled(pos, nodeEnd, nodeColor, 6.0f);
	drawList->AddRect(pos, nodeEnd, IM_COL32(255, 255, 255, 255), 6.0f);

	drawList->AddText(pos + ImVec2(25, 15), IM_COL32(255, 255, 255, 255), node->getName().c_str());

}
