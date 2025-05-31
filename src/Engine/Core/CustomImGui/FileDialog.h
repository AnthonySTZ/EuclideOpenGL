#pragma once

#include <imgui.h>
#include <string>


class FileDialog {
public:
	static std::string openDialog(std::string name, std::string label, std::string type, std::string path);

};