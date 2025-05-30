#pragma once

#include "Field.h"

#include <string>

class BooleanField : public Field {

public:
	BooleanField(const char* name, bool defaultValue = false) : label{ std::string(name) }, value{ defaultValue } {}

	void draw() override;
	int getValue() const { return value; }

private:
	std::string label;
	bool value;

};