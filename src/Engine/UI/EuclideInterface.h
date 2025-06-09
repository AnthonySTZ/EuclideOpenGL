#pragma once

#include "../Core/Rendering/EuclideRenderer.h"
#include "NodeGraph/SceneGraph.h"
#include "../Core/Nodes/NodesInfo.h"

#include <chrono>
#include <memory>


class EuclideInterface {

	using clock = std::chrono::high_resolution_clock;

public:
	EuclideInterface(GLFWwindow* window);
	void initImGui(GLFWwindow* window);
	void createRenderer();
	~EuclideInterface();
	void drawFrame();
	void createUI();
	void beginTab(const char* name, ImVec2 padding = ImVec2(0.0, 0.0), ImU32 bgCol = IM_COL32(0, 0, 0, 255));
	void createViewport();
	void createNodeGraph();
    void getSearchItems();
    void drawSearchBar();
	void drawNodesItems(ImGuiIO& io, std::vector<NodeMenuItem> items);
	void createNodesMenu();
	void updateRenderNode();
	void drawParametersTab();
	void renderUI();

	bool hasViewportResized() const { return viewportResized; };
	int getViewportWidth() const { return viewportWidth; };
	int getViewportHeight() const { return viewportHeight; };

private:
	/* VIEWPORT */
	bool viewportResized=false;
	int viewportWidth = 1200;
	int viewportHeight = 800;
	std::string searchText;
	std::vector<NodeMenuItem> searchedItems;
	bool shouldFocusSearchBar = true;

	/* FPS */
	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	float fpsIntervalInSeconds = 0.5f;
	int frameCount = 0;
	float elapsedTime = 0.0f;
	int fpsShow = 0;
	ImFont* myFont;

	void createDockSpace();
	void calcFps();

	std::unique_ptr<EuclideRenderer> renderer;
	SceneGraph sceneGraph;

};