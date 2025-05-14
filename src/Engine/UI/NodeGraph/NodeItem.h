#pragma once

#include "../../Core/Nodes/Node.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

inline ImVec2 operator+(const ImVec2& lvec, const ImVec2& rvec) {
	return ImVec2(lvec.x + rvec.x, lvec.y + rvec.y);
}

class NodeItem {

public:
	NodeItem(std::shared_ptr<Node> node, ImVec2 nodePos) : node{ node }, pos{ nodePos } {};
	NodeItem() = default;

	void draw();

	std::shared_ptr<Node> getNode() const { return node; };

private:

	ImVec2 pos;
	std::shared_ptr<Node> node;

};