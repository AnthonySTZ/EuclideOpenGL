#pragma once

#include "EuclideModel.h"
#include "EuclideCamera.h"

#include <glad/glad.h>
#include <string>
#include <vector>

class EuclideRenderer {

public:
	EuclideRenderer();
	~EuclideRenderer();

	void createShaderProgram(unsigned int &shaderProgram, std::string vertexFile, std::string fragmentFile);

	void createCamera();
	void initBuffers();

	void initFramebuffer();
	void resizeFrameBuffer(int w, int h);
	GLuint getRenderTexture() const { return renderTexture; };

	void draw() ;
	void startFrame() ;
	void endFrame() ;
	void clearFrame() ;
	void bindUniforms(unsigned int shaderProgram) ;
	void drawModel() ;
	void updateModel(Mesh::Builder& builder) { model.updateMesh(Mesh(builder)); };
	void updateMesh(Mesh mesh) { model.updateMesh(mesh); };

	void orbitCamera(float yaw, float pitch) { camera.orbit(yaw * viewSpeed, pitch * viewSpeed); };
	void panCamera(float dx, float dy) { camera.pan(glm::vec2(dx * translateSpeed, dy * translateSpeed)); };
	void zoomCamera(float delta) { camera.dolly(delta * zoomSpeed); };

	float getViewportAspectRatio() const {
		if (viewportHeight == 0) {
			return 1.0f;
		}
		return static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight);
	};

	
	static unsigned int createShader(const char* shaderSrc, GLenum type);;
	void createGrid();
	void centerCamera();

	void toogleGridVisibility() { gridShown = !gridShown; };
	void toogleWireframeVisibility() { wireframeShown = !wireframeShown; };
	void tooglePointVisibility() { pointShown = !pointShown; };
	void toogleFaceVisibility() { faceShown = !faceShown; };

	EuclideModel* getModel() { return &model; };

private:
	unsigned int facesShaderProgram;
	unsigned int wireframeShaderProgram;
	unsigned int pointsShaderProgram;
	GLuint renderTexture, FBO, depthBuffer;
	int viewportWidth, viewportHeight;

	EuclideModel model;
	EuclideModel grid;
	EuclideCamera camera;

	float translateSpeed = 0.003f;
	float viewSpeed = 0.005f;
	float zoomSpeed = 0.01f;

	bool gridShown = true;
	bool wireframeShown = true;
	bool pointShown = true;
	bool faceShown = true;
};