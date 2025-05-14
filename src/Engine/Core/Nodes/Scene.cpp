#include "Scene.h"

#include <iostream>
#include <ctype.h>

void Scene::addNode(Node* node)
{

	std::string newName = getUntakenName(node->getName());
	node->setName(newName);
	nodes[newName] = node;

}

std::string Scene::getUntakenName(std::string name) {

	if (nodes.find(name) == nodes.end()) return name;
	return getUntakenName(incrementName(name));

}

std::string Scene::incrementName(std::string name) {

	size_t i = name.length()-1;
	while (isdigit(name.at(i))) {
		i--;
	}

	if (i == name.length() - 1) return name + "1";

	std::string realName = name.substr(0, i+1);
	uint32_t num = stoi(name.substr(i+1, name.length() - i));
	num++;

	return realName + std::to_string(num);
}