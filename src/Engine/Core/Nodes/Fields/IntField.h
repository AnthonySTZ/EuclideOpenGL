#pragma once

#include "Field.h"

#include <string>

class IntField : public Field {

public:
	IntField(std::string& name, int defaultValue = 0) : label{ name }, value{ defaultValue } {}

	void draw() override;
	int getValue() const { return value; }

private:
	std::string label;
	int value;

};