#include "Float3Field.h"

static float clamp(float val, float min, float max) {

    return std::max(std::min(val, max), min);

}

void Float3Field::draw()
{
    hasChanged = false;
    if (ImGui::InputFloat3(label.c_str(), value.data())) {
        value[0] = clamp(value[0], min, max);
        value[1] = clamp(value[1], min, max);
        value[2] = clamp(value[2], min, max);
        hasChanged = true;
    }
   
}

