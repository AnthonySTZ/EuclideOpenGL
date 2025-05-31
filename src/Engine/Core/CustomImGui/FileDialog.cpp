#include "FileDialog.h"

#include <iostream>

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
        
        drawTopBar(label, padding, bgCol);
        ImGui::EndPopup();
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);

    return std::string();
}

void FileDialog::drawTopBar(std::string& label, ImVec2 &padding, ImU32& bgCol){
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 titleRectSize = ImVec2(windowSize.x, 25.0f);
    ImVec2 endTitleBar = windowPos + titleRectSize;

    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    draw_list->AddRectFilled(windowPos, endTitleBar, IM_COL32(30, 30, 30, 255));

    ImVec2 textPadding{10.0f, 4.5f};
    draw_list->AddText(windowPos + textPadding, IM_COL32(230, 230, 230, 255), label.c_str());

    float closeWidth = 35.0f;
    ImVec2 closeBtnPos = windowPos;
    closeBtnPos.x += titleRectSize.x - closeWidth;
    draw_list->AddRectFilled(closeBtnPos, endTitleBar, IM_COL32(200, 0, 0, 255));

    ImVec2 closeCrossPos = closeBtnPos + ImVec2(closeWidth*0.5f, titleRectSize.y*0.5f);
    ImU32 crossCol = IM_COL32(220, 220, 220, 255);
    drawCross(closeCrossPos, closeWidth-25.0f, crossCol, 1.0f);

    /* Check if user close the popup */
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
        ImGuiIO& io = ImGui::GetIO();
        if (io.MousePos.x > closeBtnPos.x && io.MousePos.y < endTitleBar.y){
            ImGui::CloseCurrentPopup();
        } 
    }

    ImGui::SetCursorPos(ImVec2(0.0, titleRectSize.y) + padding);
}

void FileDialog::drawCross(ImVec2 position, float length, ImU32 color, float thickness){

    float midLength = length * 0.5f;
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    ImVec2 topLeftCorner = position + ImVec2(-midLength, -midLength);
    ImVec2 topRightCorner = position + ImVec2(midLength, -midLength);
    ImVec2 bottomLeftCorner = position + ImVec2(-midLength, midLength);
    ImVec2 bottomRightCorner = position + ImVec2(midLength, midLength);
    draw_list->AddLine(topLeftCorner, bottomRightCorner, color, thickness);
    draw_list->AddLine(topRightCorner, bottomLeftCorner, color, thickness);
}