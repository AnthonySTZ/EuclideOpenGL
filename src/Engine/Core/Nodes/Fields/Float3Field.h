#pragma once

#include "Field.h"

#include <string>
#include <array>

class Float3Field : public Field {

public:
	Float3Field(const char* name,
		std::array<float, 3> defaultValue = std::array<float, 3>{ 0.0f, 0.0f, 0.0f }, float min=-FLOAT_MAXI, float max= FLOAT_MAXI)
		: label{ std::string(name) }, value{ defaultValue }, min{ min }, max{ max } {
	}

	void draw() override;
	float x() const { return value[0]; }
	float y() const { return value[1]; }
	float z() const { return value[2]; }
	glm::vec3 toVec3() const { return glm::vec3(value[0], value[1], value[2]); }


private:
	std::string label;
	std::array<float, 3> value{ 0.0f, 0.0f, 0.0f };
	float min = -FLOAT_MAXI;
	float max = FLOAT_MAXI;

};