#pragma once

#include "EuclideModel.h"

#include <glad/glad.h>
#include <string>
#include <vector>

class EuclideRenderer {

public:
	EuclideRenderer(std::string vertexFile, std::string fragmentFile, std::vector<EuclideModel> inModels);
	~EuclideRenderer();

	void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	void initBuffers();

	void initFramebuffer();
	void resizeFrameBuffer(int w, int h);
	GLuint getRenderTexture() const { return renderTexture; };

	void draw() const;
	void startFrame() const;
	void endFrame() const;
	void clearFrame() const;
	void drawModels() const;


	
	static unsigned int createShader(const char* shaderSrc, GLenum type);
private:
	unsigned int shaderProgram;
	GLuint renderTexture, FBO;
	int viewportWidth, viewportHeight;

	std::vector<EuclideModel> models;

};