#pragma once

#include <imgui.h>

#include <chrono>
#include <iostream>

#define ENABLE_TIMING

class Timer {

public:
	Timer(const char* name = "Timer") : name{ name } {
		startTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		Stop();
	}

	void Stop() {
		#ifndef ENABLE_TIMING
			return;
		#endif	
		if (stopped) return;

		stopped = true;
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << name << " : " << ms << " ms\n";
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
	const char* name;
	bool stopped = false;
};

static int StringImGuiCallBack(ImGuiInputTextCallbackData* data) {
	/* Used to resize the string for a imGui input text*/
	if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
		std::string* str = (std::string*)data->UserData;
		str->resize(data->BufTextLen);
		data->Buf = (char*)str->c_str();
	}
	return 0;
}