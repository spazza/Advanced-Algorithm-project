#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.hpp"
#include "BijectionFunction.hpp"
#include "RandomGraphGenerator.hpp"
#include "Sets.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

using namespace std;

namespace CustomGraph {

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

    vector<unsigned int> lex_p();

    list<pair<unsigned int, unsigned int>> lex_m();

    void generateRandomGraph(unsigned int num_vertices);

    void clear();

private:

    void DFS(unsigned int v, vector<pair<Vertex, bool>> &visited_vertices);
    
    vector<unsigned int> sortByLabel(vector<unsigned int> unnemberded_vertices, unordered_map<unsigned int, float> label);

    vector<unsigned int> getVerticesKeys();

    unordered_map<unsigned int, Vertex> vertices;

    unsigned int numEdges;
};

}

#endif