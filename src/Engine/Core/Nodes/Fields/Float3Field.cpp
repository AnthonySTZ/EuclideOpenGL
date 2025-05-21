#include "Float3Field.h"

void Float3Field::draw()
{
    hasChanged = false;
    if (ImGui::DragFloat3(label.c_str(), value.data(), 0.05, min, max)) {
        hasChanged = true;
    }
   
}

