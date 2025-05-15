#pragma once

#include "Field.h"

#include <string>
#include <array>

class Float3Field : public Field {

public:
	Float3Field(const std::string& name,
		std::array<float, 3> defaultValue = std::array<float, 3>{ 0.0f, 0.0f, 0.0f }, float min=-FLOAT_MAX, float max= FLOAT_MAX)
		: label{ name }, value{ defaultValue }, min{ min }, max{ max } {
	}

	void draw() override;
	float x() const { return value[0]; }
	float y() const { return value[1]; }
	float z() const { return value[2]; }

private:
	std::string label;
	std::array<float, 3> value{ 0.0f, 0.0f, 0.0f };
	float min = -FLOAT_MAX;
	float max = FLOAT_MAX;

};