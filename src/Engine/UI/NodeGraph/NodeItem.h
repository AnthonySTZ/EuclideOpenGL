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

	enum IOType {
		INPUT,
		OUTPUT
	};

	struct NodeIO {
		IOType type;
		uint32_t index;
		ImVec2 offset;
		float radius;

		void drawAt(ImVec2 pos) const;
	};

	NodeItem(std::shared_ptr<Node> node, ImVec2 nodePos) : node{ node }, nodePos{ nodePos } 
	{
		createIOs();
	};

	NodeItem() = default;

	void draw();
	void moveBy(ImVec2 delta) { 
		nodePos.x += delta.x; 
		nodePos.y += delta.y;
	}
	void setSelected(bool select) { isSelected = select; }

	std::shared_ptr<Node> getNode() const { return node; };

	bool isHovered() const;
	NodeItem::NodeIO* IOClicked(ImGuiMouseButton mouseButton) const;
	bool isClicked(ImGuiMouseButton mouseButton) const;

	ImVec2 getPosition() const { return nodePos; };

private:
	void drawNodeRect();
	void drawNodeIO();

	void createIOs();


	ImVec2 nodePos = ImVec2(0, 0);
	ImVec2 nodeSize = ImVec2(80, 40);
	ImU32 nodeColor = IM_COL32(100, 100, 150, 255);
	bool isSelected = false;
	ImU32 outlineSelectedColor = IM_COL32(255, 178, 102, 255);

	float ioPadding = 5.0f;
	float ioRadius = 6.0f;

	std::shared_ptr<Node> node;
	std::vector<NodeIO> nodeIOs;
};