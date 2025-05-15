#pragma once

#include "Field.h"

#include <string>

class FloatField : Field {

public:
	FloatField(std::string name, float defaultValue = 0.0f) : label{name}, value{defaultValue} {}

	void draw() override;
	float getValue() const;

private:
	std::string label;
	float value;

};