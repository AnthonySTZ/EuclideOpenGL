#pragma once

#include "Node.h"

#include <map>

class Scene {

public:
	Scene() = default;

	void addNode(Node node);

	static std::string incrementName(std::string name);

private:
	std::string getUntakenName(std::string name);


	std::map<std::string, Node> nodes;
};