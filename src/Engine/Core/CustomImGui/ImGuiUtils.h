#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>
#include <iostream>
#include <glad/glad.h>

#include "stb_image.h"

inline ImVec2 operator+(const ImVec2& lvec, const ImVec2& rvec) {
	return ImVec2(lvec.x + rvec.x, lvec.y + rvec.y);
}

inline ImVec2 operator-(const ImVec2& lvec, const ImVec2& rvec) {
	return ImVec2(lvec.x - rvec.x, lvec.y - rvec.y);
}

inline ImVec2 operator*(const ImVec2& lvec, const float& rval) {
	return ImVec2(lvec.x * rval, lvec.y * rval);
}

inline ImVec4 operator*(const ImVec4& lvec, const float& rval) {
	return ImVec4(lvec.x * rval, lvec.y * rval, lvec.z * rval, lvec.w);
}

inline bool operator==(const ImVec2& lvec, const ImVec2& rvec) {
	return (lvec.x == rvec.x) && (lvec.y == rvec.y);
}

inline bool operator!=(const ImVec2& lvec, const ImVec2& rvec) {
	return !(lvec == rvec);
}

static int StringImGuiCallBack(ImGuiInputTextCallbackData* data) {
	/* Used to resize the string for a imGui input text*/
	if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
		std::string* str = (std::string*)data->UserData;
		str->resize(data->BufTextLen);
		data->Buf = (char*)str->c_str();
	}
	return 0;
}

static void printImVec2(const char* name, ImVec2& vec){
	std::cout << name << " | X: " << vec.x << " | Y: " << vec.y << "\n";
}

static GLuint loadTextureFromFile(const char* filename, int* out_width, int* out_height) {
    int channels;
    unsigned char* data = stbi_load(filename, out_width, out_height, &channels, 4); // force RGBA
    if (data == NULL)
        return 0;

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // good for icons
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *out_width, *out_height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return texture_id;
}