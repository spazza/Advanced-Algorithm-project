#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Node.hpp"

struct Graph {
public:
    /**
     * Get the node corresponding to the value inserted as parameter
     * @param value number which identifies the node
     * @return pointer to the selected node, NULL pointer in case it is not found
     **/
    Node* getNode(unsigned int value);

    /**
     * Add a new node to the graph
     * @param new_node pointer to the node to be added
     **/
    void addNode(Node *new_node);

    /**
     * Add an edge between two nodes
     * @param first_node pointer to the first node of the edge
     * @param second_node pointer to the second node of the edge
     **/
    void addEdge(Node *first_node, Node *second_node);

    /**
     * Get the number of nodes in the graph
     * @return integer number of nodes
     **/
    unsigned int getDimension();

    /**
     * Print the values of nodes in the graph
     **/
    void printGraph();

    void fill_in();

    ~Graph();

private:
    /**
     * Vector of nodes inside the graph
     **/
    std::vector<Node*> nodes;
};

#endif