#include "FloatField.h"

#include <imgui.h>

void FloatField::draw()
{
    ImGui::InputFloat(label.c_str(), &value);
}

float FloatField::getValue() const
{
    return value;
}
