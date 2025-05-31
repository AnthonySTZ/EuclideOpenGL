#include "FileDialog.h"

std::string FileDialog::openDialog(std::string label, std::string type, std::string path)
{
    /*
        Open a file explorer to choose a file.
        name : ImGui key
        label : Top name of the dialog
        type : type a choosing files, separated by comma : e.g ".cpp,.txt,.h"
        path : starting path folder    
    */
    ImVec2 padding = ImVec2(0.0, 0.0);
    ImU32 bgCol = IM_COL32(0, 0, 0, 255);

    ImGuiWindowClass window_class;
    window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_AutoHideTabBar;
    ImGui::SetNextWindowClass(&window_class);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, bgCol);
    ImGui::SetNextWindowSize(ImVec2(800, 600));

    if (ImGui::BeginPopup("BrowseFile")) {
        
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 titleRectSize = ImVec2(windowSize.x, 25.0f);
        ImVec2 endTitleBar = windowPos;
        endTitleBar.y = titleRectSize.y;

        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        draw_list->AddRectFilled(windowPos, windowPos + titleRectSize, IM_COL32(30, 30, 30, 255));

        ImVec2 textPadding{10.0f, 4.5f};
        draw_list->AddText(windowPos + textPadding, IM_COL32(230, 230, 230, 255), label.c_str());

        ImGui::SetCursorPos(ImVec2(0.0, titleRectSize.y) + padding);
        ImGui::EndPopup();    
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);

    return std::string();
}
