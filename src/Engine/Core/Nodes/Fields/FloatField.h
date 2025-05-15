#pragma once

#include "Field.h"

#include <string>

class FloatField : public Field {

public:
	FloatField(std::string &name, float defaultValue = 0.0f) : label{name}, value{defaultValue} {}

	void draw() override;
	float getValue() const { return value; }

private:
	std::string label;
	float value;

};