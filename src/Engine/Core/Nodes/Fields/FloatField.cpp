#include "FloatField.h"

void FloatField::draw()
{
    hasChanged = false;
    if (ImGui::InputFloat(label.c_str(), &value)) {
        hasChanged = true;
    }
}