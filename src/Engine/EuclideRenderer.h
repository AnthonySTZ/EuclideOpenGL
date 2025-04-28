#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>

class EuclideRenderer {

public:
	EuclideRenderer(std::string vertexFile, std::string fragmentFile);
	~EuclideRenderer();

	void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	void initBuffers();

	void initFramebuffer();
	void resizeFrameBuffer(int w, int h);
	GLuint getRenderTexture() const { return renderTexture; };

	void draw() const;

	static std::string readFile(const std::string& filepath);
	static unsigned int createShader(const char* shaderSrc, GLenum type);
private:
	unsigned int shaderProgram;
	unsigned int VAO, VBO;
	GLuint renderTexture, FBO;
	int viewportWidth, viewportHeight;

	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};
};