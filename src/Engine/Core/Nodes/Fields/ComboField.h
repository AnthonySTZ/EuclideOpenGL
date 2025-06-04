#pragma once

#include "Field.h"

#include <string>
#include <vector>

class ComboField : public Field {

public:
	ComboField(const char* name, std::vector<std::string> values, int defaultValue = 0) : label{ std::string(name) }, values{values}, currValue{ defaultValue } {}

	void draw() override;
	int getValue() const { return currValue; }

private:
	std::string label;
	std::vector<std::string> values;
	int currValue;

};