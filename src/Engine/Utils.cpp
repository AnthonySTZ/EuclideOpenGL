#include "Utils.h"

#include <fstream>
#include <vector>
#include <iostream>

std::string Utils::readFile(const std::string& filepath)
{
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

	return std::string(begin(buffer), end(buffer));;
}
