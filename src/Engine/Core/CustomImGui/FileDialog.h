#pragma once

#include "ImGuiUtils.h"

#include <vector>

enum FileType {
	File,
	Folder
};

struct FileItem {
	FileType type;
	std::string name;
	std::string extension;
	std::string fileSize;
};

class FileDialog {
public:
	FileDialog(std::string label, std::string type, std::string path) :
	label{label}, type{type}, path{path} {}
	std::string drawDialog();

    void drawTopBar(std::string &label, ImVec2 &padding, ImU32 &bgCol);
    void drawCross(ImVec2 position, float length, ImU32 color, float thickness);
private:
	std::string label;
	std::string type;
	std::string path;
};