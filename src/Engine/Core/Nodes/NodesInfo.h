#pragma once

#include "Node.h"

#include <vector>
#include <functional>
#include <memory>

struct NodeMenuItem {
    const char* name;
    std::function<std::shared_ptr<Node>()> createNode;
};

class NodesInfo {
public:
    static const std::map<const char*, std::vector<NodeMenuItem>>& getMenuItems();
};