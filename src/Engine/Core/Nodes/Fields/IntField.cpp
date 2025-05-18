#include "IntField.h"

static int clamp(int val, int min, int max) {

    return std::max(std::min(val, max), min);

}

void IntField::draw()
{
    hasChanged = false;
    if (ImGui::InputInt(label.c_str(), &value)) {
        value = clamp(value, min, max);
        hasChanged = true;
    }
}