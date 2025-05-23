#pragma once

#include <chrono>
#include <iostream>

class Timer {

public:
	Timer(const char* name = "Timer") : name{ name } {
		startTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		Stop();
	}

	void Stop() {
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