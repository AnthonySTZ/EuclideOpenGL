#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>

class EuclideRenderer {

public:
	EuclideRenderer(std::string vertexFile, std::string fragmentFile);

	void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	static std::string readFile(const std::string& filepath);
	static unsigned int createShader(const char* shaderSrc, GLenum type);
private:
	unsigned int shaderProgram;
};