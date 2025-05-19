#pragma once

#include "NodeItem.h"

class NodeConnectionLine {

public:
	NodeConnectionLine(
		std::shared_ptr<NodeItem> node_1,
		NodeItem::NodeIO* nodeIO_1,
		std::shared_ptr<NodeItem> node_2,
		NodeItem::NodeIO* nodeIO_2
	);

	void rebuildConnection();

	void draw();
	static bool ccw(ImVec2 A, ImVec2 B, ImVec2 C);
	static bool intersect(ImVec2 A, ImVec2 B, ImVec2 C, ImVec2 D);
	bool intersectWithLine(ImVec2 lineStart, ImVec2 lineEnd);

	void deleteConnection();
	bool isConnectedTo(std::shared_ptr<NodeItem> node) const {
		return (node == inputNode) || (node == outputNode);
	}
	std::shared_ptr<NodeItem> getInputNode() const { return outputNode; };
	NodeItem::NodeIO* getInputIO() const { return inputIO; };
	std::shared_ptr<NodeItem> getOutputNode() const { return outputNode; };
	NodeItem::NodeIO* getOutputIO() const { return outputIO; };

private:
	std::shared_ptr<NodeItem> inputNode;
	NodeItem::NodeIO* inputIO;
	std::shared_ptr<NodeItem> outputNode;
	NodeItem::NodeIO* outputIO;

};