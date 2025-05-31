#include "ImportObj.h"

#include "../Utils.h"

Mesh ImportObj::processOutput(uint32_t index)
{

    std::string filename = getParam<FileField>("Filename")->getValue();

    return readObj(filename);
}

Mesh ImportObj::readObj(std::string filename)
{
    if (!doesFileExists(filename)) return Mesh();


    Mesh::Builder builder;
    std::ifstream file = getFile(filename);

    std::string line;

    while (getline(file, line)) {
        std::cout << line << "\n";
    }

    return Mesh();
}
