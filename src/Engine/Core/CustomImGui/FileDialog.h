#pragma once

#include "ImGuiUtils.h"

#include <vector>

enum FileType {
	File,
	Directory
};

struct FileItem {
	FileType type;
	std::string name;
	std::string extension;
	std::string fileSize;
	std::string fullPath;
};

class FileDialog {
public:
	FileDialog(std::string label, std::string type, std::string path);
    void updateFiles();
    std::string drawDialog();

    void drawTopBar(std::string &label, ImVec2 &padding, ImU32 &bgCol);
    void drawFilesTable();
    bool isRowHovered();
    void drawCross(ImVec2 position, float length, ImU32 color, float thickness);

private:
	std::string label;
	std::string type;
	std::string path;

	std::vector<FileItem> files;
};