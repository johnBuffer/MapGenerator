#include "Graph.hpp"
#include <cmath>

void Node::addNeighbour(Node* node)
{
    for (auto& nd : neighbors)
    {
        if (nd == node) return;
    }

    neighbors.push_back(node);
}

double Node::distToNode(Node* node)
{
    double vx = node->region->capital()._x - region->capital()._x;
    double vy = node->region->capital()._y - region->capital()._y;
    return sqrt(vx*vx+vy*vy);
}

Graph::Graph()
{

}

void Graph::checkRegionRegistration(Region* region)
{
    if (_reversePairs.find(region) == _reversePairs.end())
    {
        _nodes.push_back(Node(region));
        Node* newNode = &_nodes.back();
        _pairs[newNode] = region;
        _reversePairs[region] = newNode;
    }
}

void Graph::addConnection(Region* region1, Region* region2)
{
    checkRegionRegistration(region1);
    checkRegionRegistration(region2);

    _reversePairs[region1]->addNeighbour(_reversePairs[region2]);
    _reversePairs[region2]->addNeighbour(_reversePairs[region1]);
}

std::vector<Region*> Graph::getPath(Region* region1, Region* region2)
{
    std::vector<Region*> path;

    if (!region2 || !region1) return path;

    for (auto& node : _nodes)
    {
        node.marked = false;
        node.dist   = -1;
        node.last   = nullptr;
    }

    Node* node1 = _reversePairs[region1];
    Node* node2 = _reversePairs[region2];

    node1->dist = 0;
    Node* currentNode = node1;

    while (!node2->marked)
    {
        for (auto& node : currentNode->neighbors)
        {
            if (!node->marked)
            {
                double dist = currentNode->dist + currentNode->distToNode(node);

                if (dist < node->dist || node->dist == -1)
                {
                    node->dist = dist;
                    node->last = currentNode;
                }
            }
        }

        currentNode->marked = true;
        double minDist = -1;
        for (auto& node : _nodes)
        {
            if (!node.marked && node.dist > -1)
            {
                if (minDist == -1 || node.dist < minDist)
                {
                    minDist = node.dist;
                    currentNode = &node;
                }
            }
        }
    }

    Node* reversePathRegion = node2;

    while (reversePathRegion)
    {
        path.push_back(reversePathRegion->region);
        reversePathRegion = reversePathRegion->last;
    }

    return path;
}
