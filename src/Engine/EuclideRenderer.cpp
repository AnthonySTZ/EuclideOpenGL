#include "EuclideRenderer.h"
#include "Utils.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

EuclideRenderer::EuclideRenderer(std::string vertexFile, std::string fragmentFile)
{
	std::string vertCode = Utils::readFile(vertexFile);
	std::string fragCode = Utils::readFile(fragmentFile);

	unsigned int vertexShader = createShader(vertCode.c_str(), GL_VERTEX_SHADER);
	unsigned int fragmentShader = createShader(fragCode.c_str(), GL_FRAGMENT_SHADER);

	createShaderProgram(vertexShader, fragmentShader);
	initBuffers();
	initFramebuffer();
	createCamera();
}

EuclideRenderer::~EuclideRenderer()
{
	glDeleteTextures(1, &renderTexture);
	glDeleteTextures(1, &depthBuffer);
	glDeleteFramebuffers(1, &FBO);
	glDeleteProgram(shaderProgram);
	model.cleanup();	
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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void EuclideRenderer::createCamera()
{
	float aspect = getViewportAspectRatio();

	glm::vec3 position = glm::vec3(3.f, -2.f, 2.f);
	glm::vec3 target = glm::vec3(0.f, 0.f, 0.f);

	camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 1000.f);
	camera.setViewTarget(position, target);

}

void EuclideRenderer::initBuffers() {

	model.initBuffers();
}

void EuclideRenderer::initFramebuffer() {

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create texture to render to
	glGenTextures(1, &renderTexture);
	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1600, 1000, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &depthBuffer);
	glBindTexture(GL_TEXTURE_2D, depthBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1600, 1000, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Attach the depth buffer to the framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

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

	glBindTexture(GL_TEXTURE_2D, depthBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	camera.updateAspectRatio(getViewportAspectRatio());

}

void EuclideRenderer::draw()  {

	startFrame();

	clearFrame();
	bindUniforms();
	drawModel();

	endFrame();

}

void EuclideRenderer::startFrame()  {

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, viewportWidth, viewportHeight);
	glUseProgram(shaderProgram);

}

void EuclideRenderer::endFrame()  {

	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void EuclideRenderer::clearFrame()  {

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void EuclideRenderer::bindUniforms() {

	GLuint projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	glm::mat4 projection = camera.getProjection();
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint viewLocation = glGetUniformLocation(shaderProgram, "view");
	glm::mat4 view = camera.getView();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

}

void EuclideRenderer::drawModel() {

		model.draw();

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


