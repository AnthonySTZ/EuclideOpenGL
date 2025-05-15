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
	inputNode->outputs[inputIndex] = conn;

}
