#include "CuttingLine.h"

void CuttingLine::draw() const {

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddLine(startPos, endPos, IM_COL32(255, 50, 50, 255), 1.5f);

}