#include "EuclideInterface.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

#include "../Core/Utils.h"
#include "../Core/CustomImGui/ImGuiUtils.h"

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

	myFont = io.Fonts->AddFontFromFileTTF("assets/fonts/Inter/Inter.ttf", 16.0f);

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
	
	ImGui::PushFont(myFont);

	createDockSpace();

	createViewport();

	createNodeGraph();

	createGeometryTable();

	ImGui::PopFont();
	
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
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

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddRectFilled(windowPos, windowPos + titleRectSize, IM_COL32(30, 30, 30, 255));

	ImVec2 textPadding{10.0f, 4.5f};
	draw_list->AddText(windowPos + textPadding, IM_COL32(230, 230, 230, 255), name);


	ImVec2 newCursorPos = ImVec2(0.0, titleRectSize.y) + padding;
	ImGui::GetWindowDrawList()->PushClipRect(windowPos + newCursorPos, windowPos + windowSize);

	ImGui::SetCursorPos(newCursorPos);
}

void EuclideInterface::createViewport() {

	beginTab("Viewport");

	/* RENDER IMAGE */
	ImVec2 imagePos = ImGui::GetCursorScreenPos();
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();

	ImTextureID textureID = (ImTextureID)(intptr_t)renderer->getRenderTexture();
	ImGui::Image(textureID, ImVec2((float)viewportWidth, (float)viewportHeight));

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

	ImU32 infoColor = IM_COL32(200, 200, 200, 255);
	float infoTextSize = 16.0f;
	/* FPS TEXT */
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	int fpsPadding = 10;
	ImVec2 fpsPos = ImVec2(imagePos.x + fpsPadding, imagePos.y + fpsPadding);
	std::string fpsString = "Fps: " + std::to_string(fpsShow);
	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos, infoColor, fpsString.c_str());
	/* END FPS TEXT */

	/* INFO TEXT */
	size_t numPoints = renderer->getModel()->pointCount();
	size_t numPrims = renderer->getModel()->primitiveCount();
	std::string pointCountInfo = "Point count: " + std::to_string(numPoints);
	std::string polygonCountInfo = "Polygon count: "+ std::to_string(numPrims);
	

	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos + ImVec2(0, 20), infoColor, pointCountInfo.c_str());
	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos + ImVec2(0, 40), infoColor, polygonCountInfo.c_str());
																		
	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos + ImVec2(0, 60), infoColor, "Press F to recenter Camera");
	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos + ImVec2(0, 80), infoColor, "Press G to Hide/Show grid");
	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos + ImVec2(0, 100), infoColor, "Press W to Hide/Show wireframe");
	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos + ImVec2(0, 120), infoColor, "Press P to Hide/Show polygons");
	draw_list->AddText(ImGui::GetFont(), infoTextSize, fpsPos + ImVec2(0, 140), infoColor, "Press V to Hide/Show vertices");
	/* END INFO TEXT*/

	if (ImGui::IsItemHovered()) {

		if (ImGui::IsKeyPressed(ImGuiKey_F)) { // Render the selected Node
			renderer->centerCamera();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_G)) { // Show/Hide grid
			renderer->toogleGridVisibility();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_W)) { // Show/Hide wireframe
			renderer->toogleWireframeVisibility();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_P)) { // Show/Hide polygons
			renderer->toogleFaceVisibility();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_V)) { // Show/Hide vertices
			renderer->tooglePointVisibility();
		}
	}

	ImGui::GetWindowDrawList()->PopClipRect();

	ImGui::End();
}

void EuclideInterface::createNodeGraph()
{
	beginTab("NodeGraph", ImVec2(0, 0), IM_COL32(40, 40, 40, 255));

	ImVec2 topLeftWindow = ImGui::GetCursorPos();
	ImVec2 regionAvail = ImGui::GetContentRegionAvail();
	ImVec2 region = ImVec2(std::max(regionAvail.x, 100.0f), std::max(regionAvail.y, 100.0f));
	ImGui::InvisibleButton("nodegraph_click_area", region, ImGuiButtonFlags_None);
	if (
		(ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) ||
		(ImGui::IsItemHovered() && ImGui::IsKeyPressed(ImGuiKey_Tab)) ) 
	{
		ImGui::OpenPopup("node_menu");
	}

	ImGui::SetCursorPos(topLeftWindow);

	createNodesMenu();
	
	sceneGraph.drawNodes();

	drawParametersTab();

	if (sceneGraph.shouldUpdateRender()) {
		updateRenderNode();

	}

	if (!ImGui::IsPopupOpen("node_menu") && ImGui::IsKeyPressed(ImGuiKey_R)) { // Render the selected Node

		sceneGraph.setSelectedNodeRender();
		updateRenderNode();

	}

	ImGui::GetWindowDrawList()->PopClipRect();

	ImGui::End();
	
}

void EuclideInterface::createGeometryTable(){

	beginTab("Geometry Table", ImVec2(0, 0), IM_COL32(40, 40, 40, 255));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	if (ImGui::BeginChild("TableChild", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {

		int maxHeight = ImGui::GetContentRegionAvail().y;
		int textHeight = ImGui::GetTextLineHeightWithSpacing();
		int maxRows = (maxHeight / textHeight ) + 1;
		
		Mesh* mesh = renderer->getModel()->getMesh();
		int nPoints = (int)mesh->points.size();
		int numPoints = std::min(maxRows, nPoints);
		
		if (ImGui::IsWindowHovered()) {
			float scrollDelta = ImGui::GetIO().MouseWheel;
			geometryTableScroll -= scrollDelta;
			geometryTableScroll = std::clamp(geometryTableScroll, 0.0f, std::max(0.0f, (float)nPoints - maxRows + 1));
		}

		int firstIndex = (int)geometryTableScroll;
		int maxIndex = std::min(numPoints + firstIndex, nPoints);

		/* GET ALL ATTRIBS NAME */
		std::map<std::string, uint32_t> attribs;
		for (int i=firstIndex; i<maxIndex; i++) {
			for (auto& [attrName, attr]: mesh->points[i].attribs){
				if (attribs.find(attrName) != attribs.end()) continue;

				attribs[attrName] = attr->getSize();
			}
		}

		uint32_t columns = 4;
		for (const auto& [_, size] : attribs) {
			columns += size;
		}

		if (ImGui::BeginTable("GeoTable", columns, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)){
			ImGui::TableSetupColumn("Id");
			ImGui::TableSetupColumn("Pos[0]");
			ImGui::TableSetupColumn("Pos[1]");
			ImGui::TableSetupColumn("Pos[2]");

			/* ADD ATTRIBS COLUMNS */
			for (const auto& [attr, size] : attribs) {
				if (size == 1) {
					ImGui::TableSetupColumn(attr.c_str());
					continue;
				}
				for (int i = 0; i < size; i++){
					ImGui::TableSetupColumn((attr + "[" + std::to_string(i) + "]").c_str());
				}
			}

			ImGui::TableHeadersRow();			

			for (int i=firstIndex; i<maxIndex; i++) {
				
				auto& point = mesh->points[i];
				int column = 0;
				
				ImGui::TableNextRow(ImGuiTableRowFlags_None);
				ImGui::TableSetColumnIndex(column);
				ImGui::Text(std::to_string(point.id).c_str());
				column++;

				ImGui::TableSetColumnIndex(column);
				ImGui::Text(std::to_string(point.position.x).c_str());
				column++;

				ImGui::TableSetColumnIndex(column);
				ImGui::Text(std::to_string(point.position.y).c_str());
				column++;

				ImGui::TableSetColumnIndex(column);
				ImGui::Text(std::to_string(point.position.z).c_str());
				column++;


				for (const auto& [attr, size] : attribs) {
					for (int i = 0; i < size; i++){
						ImGui::TableSetColumnIndex(column);
						ImGui::Text(std::to_string(point.attribs[attr]->getValue(i)).c_str());
						column++;
					}
				}

			}
			
			ImGui::EndTable();
			
		}
	
		ImGui::EndChild();
	}
	ImGui::PopStyleVar(1);
	ImGui::End();

}

void EuclideInterface::getSearchItems() {
	searchedItems.clear();

	if (searchText[0] != '\0') {
		std::transform(searchText.begin(), searchText.end(), searchText.begin(),
			[](unsigned char c) { return std::tolower(c); });
		auto& menuItems = NodesInfo::getMenuItems();

		for (auto& [_, items] : menuItems) {
			for (auto& item : items) {

				std::string itemName = std::string(item.name);
				std::transform(itemName.begin(), itemName.end(), itemName.begin(),
					[](unsigned char c) { return std::tolower(c); });

				if (itemName.find(searchText) != std::string::npos) {
					searchedItems.push_back(item);
				}
			}
		}

	}
}

void EuclideInterface::drawSearchBar() {

	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(50, 50, 50, 255));
	if (shouldFocusSearchBar) {
		ImGui::SetKeyboardFocusHere();
		shouldFocusSearchBar = false;
	}
	if (ImGui::InputTextWithHint("##searchBar", "Search", (char*)searchText.c_str(), searchText.capacity() + 1, ImGuiInputTextFlags_CallbackResize, StringImGuiCallBack, (void*)&searchText)) {
		getSearchItems();
	}
	ImGui::PopStyleColor();

}

void EuclideInterface::drawNodesItems(ImGuiIO& io, std::vector<NodeMenuItem> items) {

	bool isSelected = false;

	for (size_t i = 0; i < items.size(); i++) {
		auto& item = items[i];

		if (ImGui::MenuItem(item.name, nullptr)) {
			sceneGraph.addNode(NodeItem(item.createNode(), io.MousePos));
		}
		if (i < items.size() - 1) {
			ImGui::Separator();
		}
	}
}

void EuclideInterface::createNodesMenu() {

	ImGuiIO& io = ImGui::GetIO();

	ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(70, 70, 70, 255));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));

	if (ImGui::BeginPopup("node_menu")) {
		auto& menuItems = NodesInfo::getMenuItems();

		drawSearchBar();		

		if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
			shouldFocusSearchBar = true;
		}

		if (searchedItems.size() > 0) {
			drawNodesItems(io, searchedItems);
		}
		else {
			for (auto& [menuName, items] : menuItems) {
				if (ImGui::BeginMenu(menuName)) {
					drawNodesItems(io, items);
					ImGui::EndMenu();
				}
			}
		}

		ImGui::EndPopup();
	}
	else {
		searchText.clear();
		searchedItems.clear();
		shouldFocusSearchBar = true;
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
}

void EuclideInterface::drawParametersTab() {

	std::shared_ptr<NodeItem> selectedNode = sceneGraph.getSelectedNode();
	if (selectedNode != nullptr) {

		beginTab("Parameters", ImVec2(10.0, 10.0), IM_COL32(50, 50, 50, 255));

		ImGui::Text("Node Name :");
		ImGui::SameLine();
		ImGui::Text(selectedNode->getNode()->getName().c_str());
		float titleSpacing = 6.0f;
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + titleSpacing);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(90, 90, 90, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(70, 70, 70, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(60, 60, 60, 255));

		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(90, 90, 90, 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(70, 70, 70, 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(60, 60, 60, 255));

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);

		selectedNode->getNode()->drawParameters();
		bool hasParamsChanged = selectedNode->getNode()->hasParamsChanged();
		if (hasParamsChanged) {
			updateRenderNode();
		}

		ImGui::PopStyleColor(6);
		ImGui::PopStyleVar(1);

		ImGui::GetWindowDrawList()->PopClipRect();

		ImGui::End();

	}
}

void EuclideInterface::updateRenderNode() {

	std::shared_ptr<NodeItem> renderNode = sceneGraph.getRenderNode();
	if (renderNode != nullptr) {

		std::cout << "\n"; // Add empty line to separate timer 
		
		Mesh mesh = renderNode->getNode()->processOutput(0);
		renderer->updateMesh(mesh);	

	}
	else {
		Mesh emptyMesh = Mesh();
		renderer->updateMesh(emptyMesh);
	}

	geometryTableScroll = 0.0f;

}

void EuclideInterface::renderUI() {
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EuclideInterface::calcFps()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> delta = currentTime - lastTime;
	lastTime = currentTime;

	float deltaTime = delta.count(); 
	frameCount++;                    
	elapsedTime += deltaTime;        

	if (elapsedTime >= fpsIntervalInSeconds) {
		fpsShow = (int)(frameCount / elapsedTime);
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