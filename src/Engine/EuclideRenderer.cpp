#include "EuclideRenderer.h"
#include "Utils.h"

#include <iostream>

EuclideRenderer::EuclideRenderer(std::string vertexFile, std::string fragmentFile, std::vector<EuclideModel> inModels) : models{inModels}
{
	std::string vertCode = Utils::readFile(vertexFile);
	std::string fragCode = Utils::readFile(fragmentFile);

	unsigned int vertexShader = createShader(vertCode.c_str(), GL_VERTEX_SHADER);
	unsigned int fragmentShader = createShader(fragCode.c_str(), GL_FRAGMENT_SHADER);

	createShaderProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
		
}

EuclideRenderer::~EuclideRenderer()
{
	glDeleteProgram(shaderProgram);
	for (auto& model : models) {
		model.cleanup();
	}
}

void EuclideRenderer::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {

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

void EuclideRenderer::initBuffers() {

	for (auto& model : models) {
		model.initBuffers();
	}
}

void EuclideRenderer::initFramebuffer() {

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create texture to render to
	glGenTextures(1, &renderTexture);
	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1600, 1000, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Attach texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

	// Check completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Framebuffer not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void EuclideRenderer::resizeFrameBuffer(int w, int h) {

	viewportWidth = w;
	viewportHeight = h;

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void EuclideRenderer::draw() const {

	startFrame();

	clearFrame();	
	drawModels();

	endFrame();

}

void EuclideRenderer::startFrame() const {

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, viewportWidth, viewportHeight);
	glUseProgram(shaderProgram);

}

void EuclideRenderer::endFrame() const {

	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void EuclideRenderer::clearFrame() const {

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void EuclideRenderer::drawModels() const {

	for (auto& model : models) {
		model.draw();
	}

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


