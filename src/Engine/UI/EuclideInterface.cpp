#include "EuclideInterface.h"

#include <string>
#include <iostream>
#include <iomanip>

#include "../Core/Nodes/Cube.h"
#include "../Core/Nodes/Grid.h"
#include "../Core/Nodes/Transform.h"
#include "../Core/Nodes/Null.h"
#include "../Core/Nodes/Subdivide.h"
#include "../Core/Nodes/Merge.h"

EuclideInterface::EuclideInterface(GLFWwindow* window) {

	initImGui(window);
	createRenderer();

}

void EuclideInterface::initImGui(GLFWwindow* window) {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

}

void EuclideInterface::createRenderer() {

	renderer = std::make_unique<EuclideRenderer>();
}

EuclideInterface::~EuclideInterface()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EuclideInterface::drawFrame() {

	createUI();
	renderer->draw();
	renderUI();

}

void EuclideInterface::createUI()
{
	if (hasViewportResized()) {
		renderer->resizeFrameBuffer(viewportWidth, viewportHeight);
	}

	calcFps();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	createDockSpace();

	createViewport();

	createNodeGraph();
	

	ImGuiIO& io = ImGui::GetIO();
	ImGui::Render();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	
}

void EuclideInterface::beginTab(const char* name, ImVec2 padding, ImU32 bgCol) {
	
	ImGuiWindowClass window_class;
	window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_AutoHideTabBar;
	ImGui::SetNextWindowClass(&window_class);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, bgCol);
	ImGui::Begin(name);
	ImGui::PopStyleVar(1);
	ImGui::PopStyleColor(1);

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 titleRectSize = ImVec2(windowSize.x, 25.0f);
	ImVec2 endTitleBar = windowPos;
	endTitleBar.y = titleRectSize.y;

	ImDrawList* draw_list = ImGui::GetForegroundDrawList();
	draw_list->AddRectFilled(windowPos, windowPos + titleRectSize, IM_COL32(35, 35, 35, 255));

	ImVec2 textPadding{15.0f, 6.0f};
	draw_list->AddText(windowPos + textPadding, IM_COL32(200, 200, 200, 255), name);

	ImGui::SetCursorPos(ImVec2(0.0, titleRectSize.y) + padding);
}

void EuclideInterface::createViewport() {

	beginTab("Viewport");

	/* RENDER IMAGE */
	ImVec2 imagePos = ImGui::GetCursorScreenPos();
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();

	ImTextureID textureID = (ImTextureID)(intptr_t)renderer->getRenderTexture();
	ImGui::Image(textureID, ImVec2(viewportWidth, viewportHeight));

	bool isHovered = ImGui::IsItemHovered();

	if (isHovered) {

		ImVec2 dragDelta = ImGui::GetIO().MouseDelta;

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
			ImGui::SetMouseCursor(ImGuiMouseSource_Pen);
			renderer->orbitCamera(-dragDelta.x, -dragDelta.y);
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
			ImGui::SetMouseCursor(ImGuiMouseSource_Pen);
			renderer->panCamera(-dragDelta.x, dragDelta.y);
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
			ImGui::SetMouseCursor(ImGuiMouseSource_Pen);
			renderer->zoomCamera(-dragDelta.y);
		}
	}

	if (viewportWidth != viewportSize.x || viewportHeight != viewportSize.y) {
		viewportResized = true;
	}
	else {
		viewportResized = false;
	}

	viewportWidth = static_cast<int>(viewportSize.x);
	viewportHeight = static_cast<int>(viewportSize.y);
	/* END RENDER IMAGE */

	/* FPS TEXT */
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	int fpsPadding = 10;
	ImVec2 fpsPos = ImVec2(imagePos.x + fpsPadding, imagePos.y + fpsPadding);
	std::string fpsString = "Fps: " + std::to_string(fpsShow);
	draw_list->AddText(ImGui::GetFont(), 16.0f, fpsPos, IM_COL32(255, 255, 255, 255), fpsString.c_str());
	/* END FPS TEXT */

	if (ImGui::IsKeyPressed(ImGuiKey_F)) { // Render the selected Node

		renderer->centerCamera();

	}

	ImGui::End();
}

void EuclideInterface::createNodeGraph()
{
	beginTab("NodeGraph", ImVec2(0, 0), IM_COL32(40, 40, 40, 255));

	ImVec2 topLeftWindow = ImGui::GetCursorPos();
	ImVec2 regionAvail = ImGui::GetContentRegionAvail();
	ImVec2 region = ImVec2(std::max(regionAvail.x, 100.0f), std::max(regionAvail.y, 100.0f));
	ImGui::InvisibleButton("nodegraph_click_area", region, ImGuiButtonFlags_None);
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
		ImGui::OpenPopup("node_menu");
	}
	ImGui::SetCursorPos(topLeftWindow);

	createNodesMenu();
	
	sceneGraph.drawNodes();

	drawParametersTab();

	if (sceneGraph.shouldUpdateRender()) {
		updateRenderNode();

	}

	if (ImGui::IsKeyPressed(ImGuiKey_R)) { // Render the selected Node

		sceneGraph.setSelectedNodeRender();
		updateRenderNode();

	}

	ImGui::End();
	
}

void EuclideInterface::createNodesMenu() {

	ImGuiIO& io = ImGui::GetIO();
	if (ImGui::BeginPopup("node_menu")) {
		if (ImGui::MenuItem("Cube")) {
			std::shared_ptr<Node> cubeNode = std::make_shared<Cube>();
			sceneGraph.addNode(NodeItem(cubeNode, io.MousePos));
		}
		if (ImGui::MenuItem("Grid")) {
			std::shared_ptr<Node> cubeNode = std::make_shared<Grid>();
			sceneGraph.addNode(NodeItem(cubeNode, io.MousePos));
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Transform")) {
			std::shared_ptr<Node> transformNode = std::make_shared<Transform>();
			sceneGraph.addNode(NodeItem(transformNode, io.MousePos));
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Merge")) {
			std::shared_ptr<Node> transformNode = std::make_shared<Merge>();
			sceneGraph.addNode(NodeItem(transformNode, io.MousePos));
		}
		/*ImGui::Separator();
		if (ImGui::MenuItem("Subdivide")) {
			std::shared_ptr<Node> nullNode = std::make_shared<Subdivide>();
			sceneGraph.addNode(NodeItem(nullNode, io.MousePos));
		}*/
		ImGui::Separator();
		if (ImGui::MenuItem("Null")) {
			std::shared_ptr<Node> nullNode = std::make_shared<Null>();
			sceneGraph.addNode(NodeItem(nullNode, io.MousePos));
		}
		ImGui::EndPopup();
	}

}

void EuclideInterface::drawParametersTab() {

	std::shared_ptr<NodeItem> selectedNode = sceneGraph.getSelectedNode();
	if (selectedNode != nullptr) {

		beginTab("Parameters", ImVec2(10.0, 10.0), IM_COL32(50, 50, 50, 255));

		ImGui::Text("Node Name :");
		ImGui::SameLine();
		ImGui::Text(selectedNode->getNode()->getName().c_str());

		selectedNode->getNode()->drawParameters();
		bool hasParamsChanged = selectedNode->getNode()->hasParamsChanged();
		if (hasParamsChanged) {
			updateRenderNode();
		}

		ImGui::End();

	}
}

void EuclideInterface::updateRenderNode() {

	std::shared_ptr<NodeItem> renderNode = sceneGraph.getRenderNode();
	if (renderNode != nullptr) {
		
		Mesh mesh = renderNode->getNode()->processOutput(0);
		renderer->updateMesh(mesh);	

	}

}

void EuclideInterface::renderUI() {
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EuclideInterface::calcFps()
{
	auto currentTime = clock::now();
	std::chrono::duration<float> delta = currentTime - lastTime;
	lastTime = currentTime;

	float deltaTime = delta.count(); 
	frameCount++;                    
	elapsedTime += deltaTime;        

	if (elapsedTime >= fpsIntervalInSeconds) {
		fpsShow = frameCount / elapsedTime;
		frameCount = 0;
		elapsedTime = 0.0f;
	}
}

void EuclideInterface::createDockSpace() {

	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("MainDockSpaceWindow", nullptr, window_flags);
	ImGui::PopStyleVar(3);


	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

	ImGui::End();
}