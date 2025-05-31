#pragma once

#include "Field.h"
#include "../../CustomImGui/FileDialog.h"

#include <string>

class FileField : public Field {

public:
	FileField(const char* name, std::set<std::string> extensions, std::string defaultPath="", std::string defaultValue = "") : label{ std::string(name) }, value{ defaultValue} {
		fileDialog.setExtensionsFilter(extensions);
		fileDialog.setPath(defaultPath);
	}

	void draw() override;
	std::string getValue() const { return std::string(value); }

private:
	std::string label;
	std::string value;

	FileDialog fileDialog{"Open File", {}, ""};

};