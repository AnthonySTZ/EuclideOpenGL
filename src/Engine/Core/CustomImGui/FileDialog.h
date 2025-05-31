#pragma once

#include "ImGuiUtils.h"


class FileDialog {
public:
	static std::string openDialog(std::string label, std::string type, std::string path);

};