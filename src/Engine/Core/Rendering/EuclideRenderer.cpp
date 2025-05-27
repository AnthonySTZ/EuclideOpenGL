#include "EuclideRenderer.h"
#include "Utils.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Nodes/Grid.h"

EuclideRenderer::EuclideRenderer()
{
	createShaderProgram(facesShaderProgram,
		"src/Engine/Core/Rendering/shaders/vertShader.vert",
		"src/Engine/Core/Rendering/shaders/fragShader.frag");

	createShaderProgram(wireframeShaderProgram,
		"src/Engine/Core/Rendering/shaders/wireframeVertShader.vert",
		"src/Engine/Core/Rendering/shaders/wireframeFragShader.frag");

	createShaderProgram(pointsShaderProgram,
		"src/Engine/Core/Rendering/shaders/pointsVertShader.vert",
		"src/Engine/Core/Rendering/shaders/pointsFragShader.frag");

	createGrid();
	initBuffers();
	initFramebuffer();
	createCamera();
}

EuclideRenderer::~EuclideRenderer()
{
	glDeleteTextures(1, &renderTexture);
	glDeleteTextures(1, &depthBuffer);
	glDeleteFramebuffers(1, &FBO);
	glDeleteProgram(facesShaderProgram);
	glDeleteProgram(wireframeShaderProgram);
	glDeleteProgram(pointsShaderProgram);
	model.cleanup();	
}

void EuclideRenderer::createGrid() {

	Mesh::Builder gridBuilder;
	int rows = 10;
	int cols = 10;
	float sizeX = 10.0f;
	float sizeZ = 10.0f;

	Mesh gridMesh = Grid::createGrid(rows, cols, sizeX, sizeZ);
	for (auto& point : gridMesh.points) {
		point.color = { .7f, .7f, .7f };
	}

	grid.updateMesh(gridMesh);

}

void EuclideRenderer::centerCamera()
{

	glm::vec3 center = model.getMesh()->getCenterPos();
	camera.updateTarget(center);

}

void EuclideRenderer::createShaderProgram(unsigned int& facesShaderProgram, std::string vertexFile, std::string fragmentFile) {

	std::string vertCode = Utils::readFile(vertexFile);
	std::string fragCode = Utils::readFile(fragmentFile);

	unsigned int vertexShader = createShader(vertCode.c_str(), GL_VERTEX_SHADER);
	unsigned int fragmentShader = createShader(fragCode.c_str(), GL_FRAGMENT_SHADER);

	facesShaderProgram = glCreateProgram();
	glAttachShader(facesShaderProgram, vertexShader);
	glAttachShader(facesShaderProgram, fragmentShader);
	glLinkProgram(facesShaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(facesShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(facesShaderProgram, 512, 0, infoLog);
		std::cout << infoLog << "\n";
		throw std::runtime_error("Shader program link failed");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void EuclideRenderer::createCamera()
{
	float aspect = getViewportAspectRatio();

	glm::vec3 position = glm::vec3(3.f, 2.f, 2.f);
	glm::vec3 target = glm::vec3(0.f, 0.f, 0.f);

	camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 1000.f);
	camera.setViewTarget(position, target);

}

void EuclideRenderer::initBuffers() {

	model.initBuffers();
	grid.initBuffers();
}

void EuclideRenderer::initFramebuffer() {

	glEnable(GL_PROGRAM_POINT_SIZE);
	glLineWidth(wireframeLineWidth);
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
	drawModel();

	endFrame();

}

void EuclideRenderer::startFrame()  {

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, viewportWidth, viewportHeight);

}

void EuclideRenderer::endFrame()  {

	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}	

void EuclideRenderer::clearFrame()  {

	//glClearColor(0.66f, 0.77f, .81f, 1.0f);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void EuclideRenderer::bindUniforms(unsigned int shaderProgram) {

	GLuint projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	glm::mat4 projection = camera.getProjection();
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint viewLocation = glGetUniformLocation(shaderProgram, "view");
	glm::mat4 view = camera.getView();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

}

void EuclideRenderer::drawModel() {
	
	if (faceShown) {
		glUseProgram(facesShaderProgram);
		bindUniforms(facesShaderProgram);
		model.drawFaces();
	}

	if (wireframeShown) {
		glUseProgram(wireframeShaderProgram);
		bindUniforms(wireframeShaderProgram);
		model.drawWireframe();
	}

	if (pointShown) {
		glUseProgram(pointsShaderProgram);
		bindUniforms(pointsShaderProgram);
		model.drawPoints();
	}

	if (gridShown) {
		glLineWidth(gridLineWidth);
		glUseProgram(wireframeShaderProgram);
		bindUniforms(wireframeShaderProgram);
		grid.drawWireframe();
		glLineWidth(wireframeLineWidth);
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