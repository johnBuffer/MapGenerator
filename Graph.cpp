#include "Graph.hpp"

void Node::addNeighbour(Node* node)
{
    for (auto& nd : neighbors)
        if (nd == node)
            return;

    neighbors.push_back(node);
}
