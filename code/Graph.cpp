#include "Graph.hpp"

void Graph::addNode(Node *new_node) {
    nodes.push_back(new_node);
}

void Graph::addEdge(Node *first_node, Node *second_node) {
    first_node->addEdge(second_node);
}

int Graph::getDimension() {
    return nodes.size();
}

void Graph::printGraph() {
    std::cout << "Graph: " << std::endl;
    for(auto node : nodes)
        std::cout << node->getValue() << std::endl;
}