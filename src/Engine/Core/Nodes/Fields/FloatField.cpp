#include "FloatField.h"

void FloatField::draw()
{
    hasChanged = false;
    if (ImGui::DragFloat(label.c_str(), &value, 0.05, min, max)) {
        hasChanged = true;
    }
}