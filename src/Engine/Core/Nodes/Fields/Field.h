#pragma once

#define FLOAT_MAX 9999999999.0f

#include <imgui.h>

class Field {

public:
	virtual ~Field() = default;
	virtual void draw() {};

};