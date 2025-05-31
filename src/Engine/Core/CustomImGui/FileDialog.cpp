#include "FileDialog.h"

#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <windows.h>

#include <algorithm>


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

std::string formatTime(time_t t) {
    std::ostringstream oss;
    std::tm* tm = std::localtime(&t); // Or std::gmtime(&t) for UTC
    if (tm)
        oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    else
        oss << "Invalid Time";
    return oss.str();
}

FileDialog::FileDialog(std::string label, std::set<std::string> extensions, std::string path)
 :	label{label}, path{path}
{
    setExtensionsFilter(extensions);
}

void FileDialog::updateFiles(){

    files.clear();
    FileItem returnFile;
    returnFile.name = "..";
    returnFile.type = Directory;
    files.push_back(returnFile);
    
    struct stat fileInfo;

    if (stat(path.c_str(), &fileInfo) != 0) { // Path is invalid

        auto drives = getSystemDrives();
        for (const auto& d : drives) {
            FileItem fi;
            fi.name = d;
            fi.fullPath = d;
            fi.type = Directory;
            files.push_back(fi);
        }
        return;
    }; 

    // Path is valid !

    for (const auto & entry : std::filesystem::directory_iterator(path)){
        if (stat(entry.path().string().c_str(), &fileInfo) != 0) continue;

        if ((fileInfo.st_mode & S_IFMT) == S_IFDIR) {
            FileItem fi;
            fi.type = Directory;
            fi.name = entry.path().filename().string();
            fi.fullPath = entry.path().string();
            files.push_back(fi);
            continue;
        }

        std::string extension = entry.path().extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(),
			[](unsigned char c) { return std::tolower(c); });
        if (extensionsFilter.find(extension) == extensionsFilter.end()) continue;
        
        FileItem fi;
        fi.type = File;
        fi.name = entry.path().filename().string();
        fi.extension = extension;
        fi.fullPath = entry.path().string();
        fi.fileSize = std::to_string(fileInfo.st_size);
        fi.createdAt = formatTime(fileInfo.st_ctime);
        fi.modifiedAt = formatTime(fileInfo.st_mtime);    

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

    if (ImGui::BeginPopup("BrowseFile", ImGuiWindowFlags_NoMove)) {
        
        drawTopBar(label, padding, bgCol);
        drawFilesTable();
        ImGui::EndPopup();
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(1);

    return std::string();
}

void FileDialog::setExtensionsFilter(std::set<std::string> extensions)
{
    std::set<std::string> lowercasedFilter;
    extensionsFilter = extensions;
    for (const auto& ext : extensionsFilter) {
        std::string lower = ext;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                    [](unsigned char c) { return std::tolower(c); });
        lowercasedFilter.insert(lower);
    }
    extensionsFilter = std::move(lowercasedFilter);
    updateFiles();
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
            path = "";
        } 
    }

    /* Handle Window Dragging */
    ImGuiIO& io = ImGui::GetIO();
    if (ImGui::IsMouseHoveringRect(windowPos, endTitleBar) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        lastMousePos = io.MousePos;
        isDragging = true;
    }

    if (isDragging) {
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
            ImVec2 dragOffset = io.MousePos - lastMousePos;
            ImGui::SetWindowPos(ImGui::GetWindowPos() + dragOffset);
            lastMousePos = io.MousePos;
        }
        else {
            isDragging = false;
        }
    }

    ImGui::SetCursorPos(ImVec2(0.0, titleRectSize.y) + padding);
}

void FileDialog::drawFilesTable(){

    if (ImGui::BeginTable("MyTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)){
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Type");
        ImGui::TableSetupColumn("Size");
        ImGui::TableSetupColumn("Modified");
        ImGui::TableSetupColumn("Created");
        ImGui::TableHeadersRow();
        int row = 0;

        float textHeight = ImGui::CalcTextSize("").y;
        float offsetY = (rowHeight - textHeight) * 0.5f;

        for (auto& file: files) {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);
            ImGui::TableSetColumnIndex(0);

            if (isRowHovered()){

                if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)){ // User clicked on current Row
                    if (file.type == Directory){
                        if (file.name == ".."){ // Go back one folder
                            path = goBackOneFolder(path);
                        } else {
                            path = file.fullPath;
                        }
                        std::cout << path << "\n";
                        updateFiles();
                    } else {
                        fileChoosed = file.fullPath;
                        ImGui::EndTable();
                        ImGui::CloseCurrentPopup();
                        isClosed = true;
                        return;
                    }

                    ImGui::EndTable();
                    return;
                    
                }

                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(0, 50, 100, 100));
            } else {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(0, 0, 0, 0));
            }

            ImVec2 cursorPos = ImGui::GetCursorPos();
            ImGui::SetCursorPosY(cursorPos.y + offsetY);

            ImGui::TableSetColumnIndex(0);
            ImGui::Text(file.name.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text(file.extension.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text(file.fileSize.c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text(file.modifiedAt.c_str());

            ImGui::TableSetColumnIndex(4);
            ImGui::Text(file.createdAt.c_str());

            row++;
        }

        ImGui::EndTable();

    }

}

std::string FileDialog::goBackOneFolder(std::string &currentPath){

    if (currentPath == "") return currentPath;

    std::string newPath = "";
    size_t endIndex = currentPath.size() - 1;
    if (currentPath[endIndex] == '\\' || currentPath[endIndex] == '/') endIndex -= 1; // Last character was a slash or backslash

    size_t charToCopy = 0;
    for (int i = endIndex; i >= 0; i--){
        if (currentPath[i] == '\\' || currentPath[i] == '/'){
            charToCopy = i + 1;
            break;
        }
    }

    for (size_t i=0; i < charToCopy; i++){
        newPath += currentPath[i];
    }

    return newPath;


}

bool FileDialog::isRowHovered() {

    ImVec2 topLeftCorner = ImGui::GetCursorScreenPos();
    ImVec2 topRightCorner = topLeftCorner + ImVec2(ImGui::GetWindowContentRegionMax().x, 0.0f);
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