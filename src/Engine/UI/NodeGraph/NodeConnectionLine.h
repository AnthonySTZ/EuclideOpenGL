#pragma once

#include "NodeItem.h"

class NodeConnectionLine {

public:
	NodeConnectionLine(
		std::shared_ptr<NodeItem> input,
		NodeItem::NodeIO* inIO,
		std::shared_ptr<NodeItem> output,
		NodeItem::NodeIO* outIO
	);

	void draw();
	static bool ccw(ImVec2 A, ImVec2 B, ImVec2 C);
	static bool intersect(ImVec2 A, ImVec2 B, ImVec2 C, ImVec2 D);
	bool intersectWithLine(ImVec2 lineStart, ImVec2 lineEnd);

	void deleteConnection();

private:
	std::shared_ptr<NodeItem> inputNode;
	NodeItem::NodeIO* inputIO;
	std::shared_ptr<NodeItem> outputNode;
	NodeItem::NodeIO* outputIO;

};