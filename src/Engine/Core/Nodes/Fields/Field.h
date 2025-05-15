#pragma once

#include <imgui.h>

class Field {

public:
	virtual ~Field() = default;
	virtual void draw() {};

};