#include "EuclideInterface.h"

EuclideInterface::EuclideInterface(GLFWwindow* window) {

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

EuclideInterface::~EuclideInterface()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EuclideInterface::createUI(ImTextureID renderTexture)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	createDockSpace();

	ImGui::Begin("Viewport");

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();

	ImTextureID textureID = renderTexture;
	ImGui::Image(textureID, ImVec2(viewportWidth, viewportHeight));

	if (viewportWidth != viewportSize.x || viewportHeight != viewportSize.y) {
		viewportResized = true;
	}
	else {
		viewportResized = false;
	}

	viewportWidth = static_cast<int>(viewportSize.x);
	viewportHeight = static_cast<int>(viewportSize.y);

	ImGui::End();

	ImGui::Begin("NodeGraph");
	ImGui::End();

	ImGuiIO& io = ImGui::GetIO();
	ImGui::Render();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	
}

void EuclideInterface::renderUI() {
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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