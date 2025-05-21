#include "IntField.h"

void IntField::draw()
{
    hasChanged = false;
    if (ImGui::DragInt(label.c_str(), &value, 1, min, max)) {
        hasChanged = true;
    }
}