#include "Float3Field.h"

void Float3Field::draw()
{
    ImGui::InputFloat3(label.c_str(), value.data());
}