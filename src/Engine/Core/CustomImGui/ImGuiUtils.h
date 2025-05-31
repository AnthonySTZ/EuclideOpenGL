#pragma once

#include <imgui.h>
#include <string>

static int StringImGuiCallBack(ImGuiInputTextCallbackData* data) {
	/* Used to resize the string for a imGui input text*/
	if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
		std::string* str = (std::string*)data->UserData;
		str->resize(data->BufTextLen);
		data->Buf = (char*)str->c_str();
	}
	return 0;
}