#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Definition of a node, its functions are used to manage the edges and the adjacent nodes in a handy way 
 **/
struct Node {
public:
    /**
     * Create a new node without edges 
     * @param value number representing the node
     **/
    Node(int value);

    /**
     * Get the value that characterizes this node
     * @return number representing the node
     **/
    int getValue();

    /**
     * Set the value that characterizes this node
     * @param value number representing the node
     **/
    void setValue(int value);

    /**
     * Get the nodes that are adjacent to the current one
     * @return pointer to the vector of adjacent nodes
     **/
    std::vector<Node*>* getAdjacentNodes();

    /**
     * Add a new edge between two nodes
     * @param new_adjacent_node pointer to the node to be added at the vector of adjacent nodes
     **/
    void addEdge(Node *new_adjacent_node);

    /**
     * Print the nodes adjacent to the current one
     **/
    void printAdjacentNodes();

private:
    /**
     * Vector of nodes adjacent to the current one
     **/
    std::vector<Node*> adjacent_nodes;

    /**
     * Value that characterizes the node
     **/
    int value;
};

#endif 