#include "BooleanField.h"

void BooleanField::draw()
{
    hasChanged = false;
    if (ImGui::Checkbox(label.c_str(), &value)) {
        hasChanged = true;
    }
}