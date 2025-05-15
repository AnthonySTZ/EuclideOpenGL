#pragma once

#include <memory>

class Node;

class NodeConnection {
	/*
	Connection between two nodes.

	Input node is the node that the connection comes from.In a vertical flow, this is the top node.
	Output node is the node that the connection goes to.In a vertical flow, this is the bottom node.
	*/
public:
	NodeConnection(std::shared_ptr<Node> inputNode, uint32_t inputIndex,
		std::shared_ptr<Node> outputNode, uint32_t outputIndex)
		: inputNode{ inputNode }, inputIndex{ inputIndex },
		outputNode{ outputNode }, outputIndex{ outputIndex } {
	}

	std::shared_ptr<Node> getInputNode() const { return inputNode; };
	std::shared_ptr<Node> getOutputNode() const { return outputNode; };

	uint32_t getInputIndex() const { return inputIndex; };
	uint32_t getOutputIndex() const { return outputIndex; };

private:
	std::shared_ptr<Node> inputNode;
	uint32_t inputIndex;
	std::shared_ptr<Node> outputNode;
	uint32_t outputIndex;
};