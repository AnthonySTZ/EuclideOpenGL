#include "ImportObj.h"

#include "../Utils.h"

Mesh ImportObj::processOutput(uint32_t index)
{

    std::string filename = getParam<FileField>("Filename")->getValue();

    return readObj(filename);
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

Mesh ImportObj::readObj(std::string filename)
{
    if (!doesFileExists(filename)) return Mesh();


    Mesh::Builder builder;
    std::ifstream file = getFile(filename);

    std::string line;

    uint32_t pointId = 0;
    while (getline(file, line)) {
        std::cout << line << "\n";
        if (line.substr(0, 2) == "v ") {
            glm::vec3 pos = stringToVec3(line.substr(2, line.length() - 2));
            builder.points.emplace_back(Point{pointId, pos});
            pointId++;            
        }
    }

    return Mesh{builder};
}
