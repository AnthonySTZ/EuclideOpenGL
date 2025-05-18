#pragma once

#include "Field.h"

#include <string>

class IntField : public Field {

public:
	IntField(const char* name, int defaultValue = 0, int min = -INT_MAXI, int max = INT_MAXI) : label{ std::string(name) }, value{ defaultValue }, min{ min }, max{ max } {}

	void draw() override;
	int getValue() const { return value; }

private:
	std::string label;
	int value;
	int min = -INT_MAXI;
	int max = INT_MAXI;

};