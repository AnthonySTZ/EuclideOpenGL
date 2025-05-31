#pragma once

#include "ImGuiUtils.h"


class FileDialog {
public:
	static std::string openDialog(std::string label, std::string type, std::string path);

    static void drawTopBar(std::string &label, ImVec2 &padding, ImU32 &bgCol);
    static void drawCross(ImVec2 position, float length, ImU32 color, float thickness);
};