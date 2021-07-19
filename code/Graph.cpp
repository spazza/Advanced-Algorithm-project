#include "Graph.hpp"

Node* Graph::getNode(unsigned int value) {
    for(auto n : nodes)
        if(n->getValue() == value)
            return n;
    return NULL;
}

void Graph::addNode(Node *new_node) {
    for(auto n : nodes)
        if(n->getValue() == new_node->getValue())
            return;
    nodes.push_back(new_node);
}

void Graph::addEdge(Node *first_node, Node *second_node) {
    first_node->addEdge(second_node);
}

unsigned int Graph::getDimension() {
    return nodes.size();
}

void Graph::printGraph() {
    std::cout << "Graph: " << std::endl;
    for(auto node : nodes)
        std::cout << node->getValue() << std::endl;
}

Graph::~Graph() {
    for(auto n : nodes)
        delete n;
}

void Graph::fill_in() {
    unsigned int n = nodes.size();
    bool test[n];
    
    for(unsigned int i = 0; i < n-1; ++i){
        
    }  
}