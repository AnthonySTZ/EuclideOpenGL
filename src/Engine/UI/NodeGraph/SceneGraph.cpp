#include "SceneGraph.h"

void SceneGraph::addNode(NodeItem nodeItem)
{

	nodeItems.push_back(nodeItem);
	scene.addNode(nodeItem.getNode());

}
