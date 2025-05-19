#include "FloatField.h"

static float clamp(float val, float min, float max) {

    return std::max(std::min(val, max), min);

}

void FloatField::draw()
{
    hasChanged = false;
    if (ImGui::InputFloat(label.c_str(), &value)) {
        value = clamp(value, min, max);
        hasChanged = true;
    }
}