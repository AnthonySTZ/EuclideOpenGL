#pragma once

#include "Node.h"

#include <map>

class Scene {

public:
	Scene() = default;

	void addNode(std::shared_ptr<Node> node);
	void deleteNode(const char* nodeName);

	static std::string incrementName(std::string name);

	std::map<std::string, std::shared_ptr<Node>> nodes;
private:
	std::string getUntakenName(std::string name);


};