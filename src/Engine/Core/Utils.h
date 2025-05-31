#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

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

static bool doesFileExists(const std::string& filepath){
	std::ifstream file{ filepath, std::ios::ate | std::ios::binary };
	if (!file.is_open()) {
		return false;
	}

	return true;
}

static std::ifstream getFile(const std::string& filepath){
	return std::ifstream{ filepath };	
}

static std::string readFile(const std::string& filepath){
	std::ifstream file{ filepath, std::ios::ate | std::ios::binary };
	if (!file.is_open()) {
		std::cout << "Failed to open file: " + filepath + "\n";
		throw std::runtime_error("Failed to open file: " + filepath);
	}

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	std::cout << filepath << " -> Open with file size: " << fileSize << " bytes\n";

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return std::string(begin(buffer), end(buffer));
}