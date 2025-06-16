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

	Node(const std::string name, void* updateCallback = nullptr) : nodeName{ name }, updateRender{updateCallback} {};
	Node() : nodeName{ "Node" } {};

	virtual ~Node() = default;

	std::string getName() const { return nodeName; };
	void setName(const std::string name) { nodeName = name; };

	uint32_t getInputsNb() const { return inputsNb; }
	uint32_t getOutputsNb() const { return outputsNb; }

	void setInput(uint32_t inputIndex, std::shared_ptr<Node> inputNode, uint32_t outputIndex = 0);
	void deleteInputConnection(uint32_t index);
	void deleteOutputConnection(uint32_t index, std::string outputNodeName, uint32_t outputIndex);
	void deleteNode();

	std::shared_ptr<Node> getInput(uint32_t index) const {
		auto it = inputs.find(index);
		if (it == inputs.end()) {
			return nullptr;
		}

		return it->second->getInputNode();
	};

	virtual Mesh& processOutput(uint32_t index, bool *updateDirty = nullptr) {
		throw std::runtime_error("process not implemented!");
	};

	void drawParameters();

	bool hasParamsChanged();
	bool isDirty() {return dirty; }
	void setDirty(bool nodeDirty) {
		if (dirty == nodeDirty) return;
		dirty = nodeDirty;

		if (!nodeDirty) return;

		// Propagate dirty to all connected output nodes
		for (auto& [outputIndex, connections]: outputs){ 
			for (auto& connection: connections) {
				auto outputNode = connection->getOutputNode();
                if (outputNode) {
                    outputNode->setDirty(true);
                }
			}
		}

	}

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
	std::map<uint32_t, std::vector<std::shared_ptr<NodeConnection>>> outputs;

	std::map<std::string, std::unique_ptr<Field>> parameters;
	std::vector<std::string> paramOrder;

	void* updateRender = nullptr;
	bool dirty = true;
};