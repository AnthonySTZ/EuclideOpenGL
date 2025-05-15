#pragma once

#include "NodeItem.h"

class NodeConnection {

	NodeConnection(
		std::shared_ptr<NodeItem> input,
		NodeItem::NodeIO* inIO,
		std::shared_ptr<NodeItem> output,
		NodeItem::NodeIO* outIO
	) : inputNode{ input }, outputNode{ output }, inputIO{ inIO }, outputIO{ outIO } {
	}

	void draw() {}

private:
	std::shared_ptr<NodeItem> inputNode;
	NodeItem::NodeIO* inputIO;
	std::shared_ptr<NodeItem> outputNode;
	NodeItem::NodeIO* outputIO;

};