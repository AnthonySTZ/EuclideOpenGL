#include "Node.h"

#include <iostream>

void Node::setInput(uint32_t inputIndex, std::shared_ptr<Node> inputNode, uint32_t outputIndex)
{

	if (inputIndex >= inputsNb) {
		std::cout << "Not enough inputs for " << getName().c_str() << " !\n";
		return;
	}

	if (outputIndex >= inputNode->outputsNb) {
		std::cout << "Not enough outputs for " << inputNode->getName().c_str() << " !\n";
		return;
	}

	auto conn = std::make_shared<NodeConnection>(inputNode, outputIndex, shared_from_this(), inputIndex);
	inputs[inputIndex] = conn;
	if (inputNode->outputs.find(inputIndex) == inputNode->outputs.end()) {
		inputNode->outputs[inputIndex] = { conn };
	}
	else {
		inputNode->outputs[inputIndex].push_back(conn);
	}
	

}

void Node::deleteInputConnection(uint32_t index)
{
	if (inputs.find(index) == inputs.end()) return;

	std::shared_ptr<NodeConnection> conn = inputs[index];
	std::shared_ptr<Node> topNode = conn->getInputNode();
	uint32_t topNodeIndex = conn->getInputIndex();

	topNode->deleteOutputConnection(topNodeIndex, getName(), index);
	inputs.erase(index);
}

void Node::deleteOutputConnection(uint32_t index, std::string outputNodeName, uint32_t outputIndex) {

	if (outputs.find(index) == outputs.end()) return;

	for (size_t i = 0; i < outputs[index].size(); i++) {
		if (outputs[index][i]->getOutputNode()->getName() != outputNodeName) continue;
		if (outputs[index][i]->getOutputIndex() != outputIndex) continue;
		outputs[index].erase(outputs[index].begin() + i);
		return;
	}

}

void Node::drawParameters()
{
	for (auto& param : paramOrder) {

		if (parameters.find(param) == parameters.end()) continue;

		parameters[param]->draw();

	}

}

bool Node::hasParamsChanged() {

	bool hasChanged = false;
	for (auto& param : paramOrder) {
		if (parameters.find(param) == parameters.end()) continue;
		hasChanged |= parameters[param]->hasValueChanged();
	}
	return hasChanged;

}
