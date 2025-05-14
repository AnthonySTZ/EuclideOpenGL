#pragma once

#include "../../Core/Nodes/Node.h"

class NodeItem {

public:
	NodeItem() = default;

	Node* getNode() const { return node; };

private:

	Node* node;

};