#include "ImportObj.h"

Mesh ImportObj::processOutput(uint32_t index)
{

    std::string filename = getParam<FileField>("Filename")->getValue();

    return readObj(filename);
}

Mesh ImportObj::readObj(std::string filename)
{
    return Mesh();
}
