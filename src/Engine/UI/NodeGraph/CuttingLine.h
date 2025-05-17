#pragma once

#include <imgui.h>
#include <imgui_impl_opengl3.h>

class CuttingLine {


public:
	CuttingLine(ImVec2 pos_1, ImVec2 pos_2) : startPos{ pos_1 }, endPos{ pos_2 } {};

	void draw() const;

private:
	ImVec2 startPos;
	ImVec2 endPos;
};