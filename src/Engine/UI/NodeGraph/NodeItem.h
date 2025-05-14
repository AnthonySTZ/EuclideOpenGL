#pragma once

#include "../../Core/Nodes/Node.h"

class NodeItem {

public:
	NodeItem(std::shared_ptr<Node> node) : node{ node } {};

	std::shared_ptr<Node> getNode() { return node; };

private:

	std::shared_ptr<Node> node;

};