#include "NodeConnectionLine.h"

void NodeConnectionLine::draw() {

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 ioInputPos = inputNode->getPosition() + inputIO->offset;
	ImVec2 ioOutputPos = outputNode->getPosition() + outputIO->offset;
	drawList->AddLine(ioInputPos, ioOutputPos, IM_COL32(170, 170, 170, 255), 1.5f);

}