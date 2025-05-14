#pragma once

#include "../../Core/Nodes/Node.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

inline ImVec2 operator+(const ImVec2& lvec, const ImVec2& rvec) {
	return ImVec2(lvec.x + rvec.x, lvec.y + rvec.y);
}

inline ImVec2 operator-(const ImVec2& lvec, const ImVec2& rvec) {
	return ImVec2(lvec.x - rvec.x, lvec.y - rvec.y);
}

inline ImVec2 operator*(const ImVec2& lvec, const float& rval) {
	return ImVec2(lvec.x + rval, lvec.y + rval);
}

class NodeItem {

public:
	NodeItem(std::shared_ptr<Node> node, ImVec2 nodePos) : node{ node }, nodePos{ nodePos } {};
	NodeItem() = default;

	void draw();
	void moveBy(ImVec2 delta) { 
		nodePos.x += delta.x; 
		nodePos.y += delta.y;
	}

	std::shared_ptr<Node> getNode() const { return node; };

	bool isHovered() const;
	bool isClicked(ImGuiMouseButton mouseButton) const;

private:

	ImVec2 nodePos;
	ImVec2 nodeSize = ImVec2(80, 40);
	ImU32 nodeColor = IM_COL32(100, 100, 150, 255);

	std::shared_ptr<Node> node;

};