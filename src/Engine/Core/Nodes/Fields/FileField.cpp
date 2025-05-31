#include "FileField.h"

#include "../../Utils.h"

void FileField::draw()
{

    hasChanged = false;
    if (ImGui::InputText(label.c_str(), (char*)value.c_str(), value.capacity() + 1, ImGuiInputTextFlags_CallbackResize, StringImGuiCallBack, (void*)&value)) {
        hasChanged = true;
    }

}
