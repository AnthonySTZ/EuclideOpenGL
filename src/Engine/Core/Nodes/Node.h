#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

#include "NodeConnection.h"
#include "../Geometry/Geometry.h"

#include "Fields/Field.h"

#include <vector>

class Node : public std::enable_shared_from_this<Node> {

public:

	Node(const std::string name) : nodeName{ name } {};
	Node() : nodeName{ "Node" } {};

	virtual ~Node() = default;

	std::string getName() const { return nodeName; };
	void setName(const std::string name) { nodeName = name; };

	uint32_t getInputsNb() const { return inputsNb; }
	uint32_t getOutputsNb() const { return outputsNb; }

	void setInput(uint32_t inputIndex, std::shared_ptr<Node> inputNode, uint32_t outputIndex = 0);
	std::shared_ptr<Node> getInput(uint32_t index) const {
		auto it = inputs.find(index);
		if (it == inputs.end()) {
			return nullptr;
		}

		return it->second->getInputNode();
	};

	virtual Mesh processOutput(uint32_t index) {
		throw std::runtime_error("process not implemented!");
	};

	void drawParameters();

	template<typename T>
	T* getParam(const std::string& name) {
		auto it = parameters.find(name);
		if (it != parameters.end()) {
			return dynamic_cast<T*>(it->second.get());
		}
		return nullptr;
	}

protected:
	std::string nodeName;

	uint32_t inputsNb = 0;
	uint32_t outputsNb = 0;

	std::map<uint32_t, std::shared_ptr<NodeConnection>> inputs;
	std::map<uint32_t, std::shared_ptr<NodeConnection>> outputs;

	std::map<std::string, std::unique_ptr<Field>> parameters;
	std::vector<std::string> paramOrder;

};