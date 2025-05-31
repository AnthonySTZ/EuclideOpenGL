#include "EuclideRenderer.h"
#include "../Utils.h"

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
	glDeleteTextures(1, &textureColorBufferMultiSampled);
	glDeleteRenderbuffers(1, &rboDepth);
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
		point.attribs["Color"] = std::make_unique<Float3Attrib>(glm::vec3(.5f, .5f, .5f));
	}

	grid.updateMesh(gridMesh);

}

void EuclideRenderer::centerCamera()
{

	glm::vec3 center = model.getMesh()->getCenterPos();
	camera.updateTarget(center);

}

void EuclideRenderer::createShaderProgram(unsigned int& facesShaderProgram, std::string vertexFile, std::string fragmentFile) {

	std::string vertCode = readFile(vertexFile);
	std::string fragCode = readFile(fragmentFile);

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

	// Setup multisampled FBO
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create multisampled color texture
	glGenTextures(1, &textureColorBufferMultiSampled);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, 1600, 1000, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);

	// Create multisampled depth renderbuffer (easier for depth)
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT, 1600, 1000);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	// Check completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Multisampled framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Create a separate regular FBO with a single-sample color texture for resolving

	glGenFramebuffers(1, &intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);

	glGenTextures(1, &renderTexture);
	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1600, 1000, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Intermediate framebuffer not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void EuclideRenderer::resizeFrameBuffer(int w, int h) {

	viewportWidth = w;
	viewportHeight = h;

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, w, h, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D, renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT, w, h);

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
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
	glBlitFramebuffer(0, 0, viewportWidth, viewportHeight, 0, 0, viewportWidth, viewportHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);

}	

void EuclideRenderer::clearFrame()  {

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