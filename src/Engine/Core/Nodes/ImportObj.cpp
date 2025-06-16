#include "ImportObj.h"

#include <filesystem>

#include "../Utils.h"



Mesh& ImportObj::processOutput(uint32_t index, bool *updateDirty)
{

    if (!isDirty()){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    std::string filename = getParam<FileField>("Filename")->getValue();

    Timer timer{nodeName.c_str()};

    cachedMesh = readObj(filename);

    if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}

glm::vec3 stringToVec3(std::string string){
    float output[3] = {0.f, 0.f, 0.f};

    size_t currIndex = 0;
    size_t leftPointer = 0;
    for (size_t i=0; i<string.length(); i++){

        if (currIndex == 3) break;
        if (i == string.length() - 1 || string[i] == ' ') {
            if (i > leftPointer) {
                std::string token = string.substr(leftPointer, i - leftPointer);
                output[currIndex] = std::stof(token);
                currIndex++;
            }
            leftPointer = i + 1;
        }

    }
    return glm::vec3(output[0], output[1], output[2]);
}

std::vector<uint32_t> getPointIdsFromFaceString(std::string string){

    std::vector<uint32_t> ids;

    std::vector<std::string> facesInfo;

    size_t leftPointer = 0;
    for (size_t i=0; i<string.length(); i++){

        if (i == string.length() - 1 || string[i] == ' ') {
            std::string token = string.substr(leftPointer, i - leftPointer);
            facesInfo.push_back(token);
            leftPointer = i+1;
        }

    }

    ids.reserve(facesInfo.size());

    for (auto& faceInfo: facesInfo){
        std::string currId = "";
        for(auto& c: faceInfo){
            if (c == '/') break;
            currId += c;
        }
        ids.push_back(static_cast<uint32_t>(std::stoi(currId) - 1));
    }

    return ids;
}

Mesh ImportObj::readObj(std::string filename)
{
    if (!doesFileExists(filename)) return Mesh();
    std::filesystem::path filePath(filename);
    if (filePath.extension().string() != ".obj") return Mesh();

    Mesh::Builder builder;
    std::ifstream file = getFile(filename);

    std::string line;

    uint32_t pointId = 0;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "v ") { // Add vertex
            glm::vec3 pos = stringToVec3(line.substr(2, line.length() - 2));
            builder.points.emplace_back(Point{pointId, pos});
            pointId++; 
            continue;           
        }

        if (line.substr(0, 2) == "f ") {
            std::vector<uint32_t> pointIds = getPointIdsFromFaceString(line.substr(2, line.length() - 2));
            builder.faces.emplace_back(Face{pointIds});      
        }
    }

    return Mesh{builder};
}
