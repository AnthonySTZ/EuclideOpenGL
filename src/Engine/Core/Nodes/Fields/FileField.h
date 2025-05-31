#pragma once

#include "Field.h"

#include <string>

class FileField : public Field {

public:
	FileField(const char* name, std::string defaultValue = "") : label{ std::string(name) }, value{ defaultValue} {}

	void draw() override;
	std::string getValue() const { return std::string(value); }

private:
	std::string label;
	std::string value;

};