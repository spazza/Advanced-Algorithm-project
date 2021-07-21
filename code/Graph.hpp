#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

struct Vertex {
public:

    unsigned int value;

    Vertex() = default;

    Vertex(unsigned int value);

    void addAdjacentVertex(unsigned int vertex);

    bool isAdjacent(unsigned int vertex);

    void printAdjacentVertices();

private:
    list<unsigned int> adjVertices;   
};

struct Graph {
public:

    Graph() = default;

    Graph(list<unsigned int> const &vertices);

    Graph(list<unsigned int> const &vertices, vector<unsigned int> const &sources, vector<unsigned int> const &destinations); 
 
    void addVertex(unsigned int vertex);

    void addEdge(unsigned int src, unsigned int dst);

    unsigned int size();

    list<Vertex>& getVertices();

    bool isInTheGraph(unsigned int vertex);

    void printVertices();

    void printGraph();


private:

    list<Vertex> vertices;
};



#endif