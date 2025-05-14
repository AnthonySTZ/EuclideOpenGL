#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

#include "NodeConnection.h"
#include "../Geometry/Geometry.h"

class Node {

public:

	Node(const std::string name) : nodeName{ name } {};
	Node() : nodeName{ "Node" } {};

	virtual ~Node() = default;

	std::string getName() const { return nodeName; };
	void setName(const std::string name) { nodeName = name; };

	uint32_t getInputsNb() const { return inputsNb; }
	uint32_t getOutputsNb() const { return outputsNb; }

	void setInput(uint32_t inputIndex, Node* inputNode, uint32_t outputIndex = 0);
	Node* getInput(uint32_t index) const {
		auto it = inputs.find(index);
		if (it == inputs.end()) {
			return nullptr;
		}

		return it->second->getInputNode();
	};

	virtual Mesh processOutput(uint32_t index) {
		throw std::runtime_error("process not implemented!");
	};

protected:
	std::string nodeName;

	uint32_t inputsNb = 0;
	uint32_t outputsNb = 0;

	std::map<uint32_t, std::shared_ptr<NodeConnection>> inputs;
	std::map<uint32_t, std::shared_ptr<NodeConnection>> outputs;

};