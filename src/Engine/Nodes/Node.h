#pragma once

#include <map>
#include <string>

class Node {

public:

	Node(std::string name) : nodeName{ name } {};
	Node() : nodeName{ "Node" } {};

private:
	std::string nodeName;

	uint32_t inputsNb = 0;
	uint32_t outputsNb = 0;

	std::map<uint32_t, Node> inputs;
	std::map<uint32_t, Node> outputs;

};