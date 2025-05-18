#pragma once

#define FLOAT_MAXI 9999999999.0f
#define INT_MAXI int(9999999999)

#include <imgui.h>
#include <glm/glm.hpp>

class Field {

public:
	virtual ~Field() = default;
	virtual void draw() {};
	bool hasValueChanged() const { return hasChanged; };
protected:
	bool hasChanged = false;

};