#include "EuclideRenderer.h"
#include "Utils.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	float spacing = 1.0f;

	float rowsOffset = rows * spacing * 0.5f;
	float colsOffset = cols * spacing * 0.5f;

	for (int row = 0; row <= rows; row++) {
		for (int col = 0; col <= cols; col++) {
			float x = col * spacing - rowsOffset;
			float z = row * spacing - colsOffset;
			float y = 0.0f; // flat on XZ plane

			glm::vec3 position = { x, y, z };
			glm::vec3 normal = { 0.0f, 1.0f, 0.0f };
			glm::vec3 color = { 0.8f, 0.8f, 0.8f };

			gridBuilder.vertices.push_back({ position, color, normal });
		}
	}

	// Generate quad faces
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			int topLeft = row * (cols + 1) + col;
			int topRight = topLeft + 1;
			int bottomLeft = topLeft + (cols + 1);
			int bottomRight = bottomLeft + 1;

			Face quad;
			quad.vertexIndices = {
				static_cast<uint32_t>(topLeft),
				static_cast<uint32_t>(bottomLeft),
				static_cast<uint32_t>(bottomRight),
				static_cast<uint32_t>(topRight)
			};
			gridBuilder.faces.push_back(quad);
		}
	}

	grid.updateMesh(gridBuilder);

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
	glLineWidth(1.5f);
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
	glUseProgram(facesShaderProgram);

}

void EuclideRenderer::endFrame()  {

	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void EuclideRenderer::clearFrame()  {

	glClearColor(0.66f, 0.77f, .81f, 1.0f);
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
	
	glUseProgram(facesShaderProgram);
	bindUniforms(facesShaderProgram);
	model.drawFaces();

	glUseProgram(wireframeShaderProgram);
	bindUniforms(wireframeShaderProgram);
	model.drawWireframe();

	glUseProgram(pointsShaderProgram);
	bindUniforms(pointsShaderProgram);
	model.drawPoints();

	glUseProgram(wireframeShaderProgram);
	bindUniforms(wireframeShaderProgram);
	grid.drawWireframe();

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