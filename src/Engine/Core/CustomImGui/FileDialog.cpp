#include "FileDialog.h"

std::string FileDialog::openDialog(std::string name, std::string label, std::string type, std::string path)
{
    /*
        Open a file explorer to choose a file.
        name : ImGui key
        label : Top name of the dialog
        type : type a choosing files, separated by comma : e.g ".cpp,.txt,.h"
        path : starting path folder    
    */
    if (ImGui::BeginPopup("BrowseFile")) {
        ImGui::Text("Hello from the popup!");
        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
    
    return std::string();
}
