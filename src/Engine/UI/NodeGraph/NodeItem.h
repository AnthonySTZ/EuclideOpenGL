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
	return ImVec2(lvec.x * rval, lvec.y * rval);
}

inline ImVec4 operator*(const ImVec4& lvec, const float& rval) {
	return ImVec4(lvec.x * rval, lvec.y * rval, lvec.z * rval, lvec.w);
}

inline bool operator==(const ImVec2& lvec, const ImVec2& rvec) {
	return (lvec.x == rvec.x) && (lvec.y == rvec.y);
}

inline bool operator!=(const ImVec2& lvec, const ImVec2& rvec) {
	return !(lvec == rvec);
}

class NodeItem {

public:

	enum IOType {
		INPUT,
		OUTPUT
	};

	struct NodeIO {
		IOType type = INPUT;
		uint32_t index = 0;
		ImVec2 offset = ImVec2(0.0, 0.0);
		float radius = 5.0f;

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
	NodeItem::NodeIO* getIOUnderMouse() const;
	bool isClicked(ImGuiMouseButton mouseButton) const;
	void setRenderState(bool renderState) { isRender = renderState; }

	ImVec2 getPosition() const { return nodePos; };

private:
	void drawNodeRect();
	void drawNodeIO();

	void createIOs();

	ImU32 vec4ToColor(ImVec4 col) { return IM_COL32(col.x, col.y, col.z, col.w); }


	ImVec2 nodePos = ImVec2(0, 0);
	ImVec2 nodeSize = ImVec2(80, 40);
	ImVec4 nodeColor = ImVec4(100, 100, 150, 255);
	ImVec4 nodeRenderColor = ImVec4(181, 72, 94, 255);
	bool isSelected = false;
	ImVec4 outlineSelectedColor = ImVec4(255, 178, 102, 255);
	bool isRender = false;

	float ioPadding = 5.0f;
	float ioRadius = 6.0f;

	std::shared_ptr<Node> node;
	std::vector<NodeIO> nodeIOs;
};