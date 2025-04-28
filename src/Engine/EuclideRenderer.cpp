#include "EuclideRenderer.h"

#include <fstream>
#include <iostream>

EuclideRenderer::EuclideRenderer(std::string vertexFile, std::string fragmentFile)
{
	std::string vertCode = readFile(vertexFile);
	std::string fragCode = readFile(fragmentFile);

	vertexShader = createShader(vertCode.c_str(), GL_VERTEX_SHADER);
	fragmentShader = createShader(fragCode.c_str(), GL_FRAGMENT_SHADER);

	createShaderProgram();
		
}

void EuclideRenderer::createShaderProgram() {

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
		std::cout << infoLog << "\n";
		throw std::runtime_error("Shader program link failed");
	}
}

std::string EuclideRenderer::readFile(const std::string& filepath)
{
	std::ifstream file{ filepath, std::ios::ate | std::ios::binary };
	if (!file.is_open()) {
		std::cout << "Failed to open file: " + filepath + "\n";
		throw std::runtime_error("Failed to open file: " + filepath);
	}

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	std::cout << "file size: " << fileSize << "\n";

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return std::string(begin(buffer), end(buffer));;
}

unsigned int EuclideRenderer::createShader(const char* shaderSrc, GLenum type)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSrc, 0);
	glCompileShader(shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		std::cout << infoLog << "\n";
		throw std::runtime_error("Shader compilation failed");
	}

	return shader;
}


