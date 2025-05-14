#include "EuclideInterface.h"

#include <string>
#include <iostream>
#include <iomanip>

#include "../Core/Nodes/Cube.h"
#include "../Core/Nodes/Transform.h"
#include "../Core/Nodes/Null.h"

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

void EuclideInterface::createViewport() {

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Viewport");	

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
			renderer->orbitCamera(-dragDelta.x, dragDelta.y);
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
			ImGui::SetMouseCursor(ImGuiMouseSource_Pen);
			renderer->panCamera(-dragDelta.x, -dragDelta.y);
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

	ImGui::End();
	ImGui::PopStyleVar(1);
}

void EuclideInterface::createNodeGraph()
{
	ImGui::Begin("NodeGraph");

	ImGuiIO& io = ImGui::GetIO();

	ImVec2 region = ImGui::GetContentRegionAvail();
	ImVec2 startPos = ImGui::GetCursorScreenPos();
	ImVec2 endPos = startPos + region;

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(startPos, endPos, IM_COL32(50, 50, 50, 255));

	ImGui::SetCursorScreenPos(startPos); // Reset cursor
	ImGui::InvisibleButton("nodegraph_click_area", region, ImGuiButtonFlags_None);
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
		ImGui::OpenPopup("node_menu");
	}

	if (ImGui::BeginPopup("node_menu")) {
		if (ImGui::MenuItem("Cube")) {
			std::shared_ptr<Node> cubeNode = std::make_shared<Cube>();
			sceneGraph.addNode(NodeItem(cubeNode, io.MousePos));
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Transform")) {
			std::shared_ptr<Node> transformNode = std::make_shared<Transform>();
			sceneGraph.addNode(NodeItem(transformNode, io.MousePos));
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Null")) {
			std::shared_ptr<Node> nullNode = std::make_shared<Null>();
			sceneGraph.addNode(NodeItem(nullNode, io.MousePos));
		}
		ImGui::EndPopup();
	}

	sceneGraph.drawNodes();

	ImGui::End();
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