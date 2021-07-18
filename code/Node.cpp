#include "Node.hpp"

Node::Node(int value) { 
    this->value = value; 
}

int Node::getValue() {
    return value;
}

void Node::setValue(int value) {
    this->value = value;
}

std::vector<Node*>* Node::getAdjacentNodes() {
    return &adjacent_nodes;
}

void Node::addEdge(Node *new_adjacent_node) {
    if(std::find(adjacent_nodes.begin(), adjacent_nodes.end(), new_adjacent_node) != adjacent_nodes.end())
        return;

    adjacent_nodes.push_back(new_adjacent_node);
    new_adjacent_node->getAdjacentNodes()->push_back(this);
}

void Node::printAdjacentNodes() {
    std::cout << "Nodes adjacent to node " << this->getValue() << " : ";
    for(auto adj_node : adjacent_nodes)
        std::cout << " -> " << adj_node->getValue();  
    std::cout << std::endl;
}
