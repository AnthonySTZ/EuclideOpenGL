#include "ComboField.h"

void ComboField::draw()
{
    hasChanged = false;
    if (ImGui::Combo("Fruits", &currValue, [](void* data, int idx, const char** out_text) {
        const auto& vec = *static_cast<std::vector<std::string>*>(data);
        if (idx < 0 || idx >= vec.size()) return false;
        *out_text = vec[idx].c_str();
        return true;
    }, static_cast<void*>(&values), values.size())) {
        hasChanged = true;
    }
}