#include "FileDialog.h"

#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <windows.h>

std::vector<std::string> getSystemDrives() {
    std::vector<std::string> drives;
    char szDrives[256] = {0};

    if (GetLogicalDriveStringsA(sizeof(szDrives), szDrives)) {
        char* drive = szDrives;
        while (*drive) {
            drives.emplace_back(drive);
            drive += strlen(drive) + 1;
        }
    }

    return drives;
}

FileDialog::FileDialog(std::string label, std::string type, std::string path)
 :	label{label}, type{type}, path{path}
{
    updateFiles();
}

void FileDialog::updateFiles(){

    files.clear();
    struct stat fileInfo;

    if (stat(path.c_str(), &fileInfo) != 0) { // Path is invalid

        auto drives = getSystemDrives();
        for (const auto& d : drives) {
            FileItem fi;
            fi.name = d;
            fi.type = Directory;
            files.push_back(fi);
        }
        return;
    }; 

    // Path is valid !

    for (const auto & entry : std::filesystem::directory_iterator(path)){
        if (stat(entry.path().string().c_str(), &fileInfo) != 0) continue;

        FileItem fi;
        fi.name = entry.path().filename().string();
        fi.extension = entry.path().extension().string();

        if ((fileInfo.st_mode & S_IFMT) == S_IFDIR) { // From sys/types.h
            fi.type = Directory;
        } else {
            fi.type = File;
            fi.fileSize = std::to_string(fileInfo.st_size);
        }

        files.push_back(fi);
    }


}

std::string FileDialog::drawDialog()
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
        drawFilesTable();
        ImGui::EndPopup();
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);

    return std::string();
}

void FileDialog::drawTopBar(std::string &label, ImVec2 &padding, ImU32 &bgCol)
{
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

void FileDialog::drawFilesTable(){

    if (ImGui::BeginTable("MyTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)){
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Type");
        ImGui::TableSetupColumn("Size");
        ImGui::TableHeadersRow();    

        int row = 0;
        for (auto& file: files) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);

            if (isRowHovered()){
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(0, 50, 100, 100));
            } else {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(0, 0, 0, 0));
            }

            ImGui::TableSetColumnIndex(0);
            ImGui::Text(file.name.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text(file.extension.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text(file.fileSize.c_str());

            row++;
        }

        ImGui::EndTable();

    }

}

bool FileDialog::isRowHovered() {

    ImVec2 topLeftCorner = ImGui::GetCursorScreenPos();
    ImVec2 topRightCorner = topLeftCorner + ImVec2(ImGui::GetWindowContentRegionMax().x, 0.0f);
    float rowHeight = ImGui::GetTextLineHeight();
    ImVec2 bottomLeftCorner = topLeftCorner + ImVec2(0.0f, rowHeight);

    ImGuiIO& io = ImGui::GetIO();

    if (io.MousePos.x > topLeftCorner.x &&  io.MousePos.x < topRightCorner.x &&
        io.MousePos.y > topLeftCorner.y && io.MousePos.y < bottomLeftCorner.y) 
    {
        return true;
    }
    return false;
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