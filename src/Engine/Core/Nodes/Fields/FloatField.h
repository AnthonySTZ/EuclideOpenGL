#pragma once

#include "Field.h"

#include <string>

class FloatField : public Field {

public:
	FloatField(const char* name, float defaultValue = 0.0f, float min=-FLOAT_MAXI, float max=FLOAT_MAXI)
		: label{ std::string(name) }, value{ defaultValue }, min{min}, max { max } {}

	void draw() override;
	float getValue() const { return value; }

private:
	std::string label;
	float value;
	float min = -FLOAT_MAXI;
	float max = FLOAT_MAXI;

};