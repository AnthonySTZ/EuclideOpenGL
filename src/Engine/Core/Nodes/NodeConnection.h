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
	NodeConnection(Node* inputNode, uint32_t inputIndex,
		Node* outputNode, uint32_t outputIndex)
		: inputNode{ inputNode }, inputIndex{ inputIndex },
		outputNode{ outputNode }, outputIndex{ outputIndex } {
	}

	Node* getInputNode() const { return inputNode; };
	Node* getOutputNode() const { return outputNode; };

	uint32_t getInputIndex() const { return inputIndex; };
	uint32_t getOutputIndex() const { return outputIndex; };

private:
	Node* inputNode;
	uint32_t inputIndex;
	Node* outputNode;
	uint32_t outputIndex;
};