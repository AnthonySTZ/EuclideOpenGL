#pragma once

#include "EuclideModel.h"
#include "EuclideCamera.h"

#include <glad/glad.h>
#include <string>
#include <vector>

class EuclideRenderer {

public:
	EuclideRenderer(std::string vertexFile, std::string fragmentFile);
	EuclideRenderer() = default;
	~EuclideRenderer();

	void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	void createCamera();
	void initBuffers();

	void initFramebuffer();
	void resizeFrameBuffer(int w, int h);
	GLuint getRenderTexture() const { return renderTexture; };

	void draw() ;
	void startFrame() ;
	void endFrame() ;
	void clearFrame() ;
	void bindUniforms() ;
	void drawModel() ;
	void updateModel(const EuclideModel::Builder& builder) { model.update(builder); };

	float getViewportAspectRatio() const {
		if (viewportHeight == 0) {
			return 1.0f;
		}
		return static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight);
	};

	
	static unsigned int createShader(const char* shaderSrc, GLenum type);
private:
	unsigned int shaderProgram;
	GLuint renderTexture, FBO, depthBuffer;
	int viewportWidth, viewportHeight;

	EuclideModel model;
	EuclideCamera camera;

};