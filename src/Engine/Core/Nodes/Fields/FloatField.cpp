#include "FloatField.h"

void FloatField::draw()
{
    ImGui::InputFloat(label.c_str(), &value);
}