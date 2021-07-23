#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.hpp"
#include "BijectionFunction.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <random>

using namespace std;

struct Graph {
public:

    Graph();

    Graph(const vector<unsigned int> &vertices);

    Graph(const vector<unsigned int> &vertices, const vector<unsigned int> &sources, const vector<unsigned int> &destinations); 
 
    void addVertex(unsigned int vertex);

    void addVertex(const Vertex &vertex);

    void addEdge(unsigned int first, unsigned int second);

    void addEdge(const Vertex &first, const Vertex &second);

    unsigned int size();

    unsigned int edgeSize();

    unordered_map<unsigned int, Vertex>& getVertices();

    bool isInside(unsigned int vertex);

    bool isInside(const Vertex &vertex);

    bool isConnected();

    void connect();

    void printGraph();

    void fill_in(BijectionFunction bijFunction);

    void generateRandomGraph(unsigned int num_nodes);

    void clear();

private:

    void DFS(unsigned int v, vector<pair<Vertex, bool>> &visited_vertices);

    unordered_map<unsigned int, Vertex> vertices;

    unsigned int numEdges;
};

#endif