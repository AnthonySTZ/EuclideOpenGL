#pragma once

#include <map>
#include <string>
#include <memory>

class Node {

public:

	Node(std::string name) : nodeName{ name } {};
	Node() : nodeName{ "Node" } {};

	virtual ~Node() = default;

	std::string getName() const { return nodeName; };
	void setName(std::string name) { nodeName = name; };

	uint32_t getInputsNb() const { return inputsNb; }
	uint32_t getOutputsNb() const { return outputsNb; }

	std::string nodeName;

protected:
	uint32_t inputsNb = 0;
	uint32_t outputsNb = 0;

	std::map<uint32_t, std::shared_ptr<Node>> inputs;
	std::map<uint32_t, std::shared_ptr<Node>> outputs;

};