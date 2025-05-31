#pragma once

#include "ImGuiUtils.h"

#include <vector>
#include <set>

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
	std::string createdAt;
	std::string modifiedAt;
};

class FileDialog {
public:
	FileDialog(std::string label, std::set<std::string> extensions, std::string path);
    void updateFiles();
    std::string drawDialog();

	void setExtensionsFilter(std::set<std::string> extensions);
	void setPath(std::string newPath) {
		path = newPath;
		updateFiles();
	}

	bool hasChooseFile() {
		if (isClosed) {
			isClosed = false;
			return true;
		}
		return false;
	}

    void drawTopBar(std::string &label, ImVec2 &padding, ImU32 &bgCol);
    void drawFilesTable();
    std::string goBackOneFolder(std::string &currentPath);
    bool isRowHovered();
    void drawCross(ImVec2 position, float length, ImU32 color, float thickness);

	std::string getChoosedFile() { return fileChoosed; };
private:
	std::string label;
	std::set<std::string> extensionsFilter;
	std::string path;
	std::string fileChoosed;


	std::vector<FileItem> files;

	float rowHeight = 30.0f;
	ImVec2 lastMousePos;
	bool isDragging = false;
	bool isClosed = false;
};