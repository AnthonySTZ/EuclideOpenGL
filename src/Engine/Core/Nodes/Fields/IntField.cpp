#include "IntField.h"

void IntField::draw()
{
    hasChanged = false;
    if (ImGui::InputInt(label.c_str(), &value)) {
        hasChanged = true;
    }
}