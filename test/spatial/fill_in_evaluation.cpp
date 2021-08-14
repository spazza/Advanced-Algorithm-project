#include "Graph.hpp"
#include <iostream>

using namespace std;

// Trivial program to test fill-in function
// Insert as first main parameter the number of elements of the graph.
// N.B. num_elements = num_vertices + num_edges

int main(int argc, char *argv[]) {
    unsigned int n = stoi(argv[1]);

    CustomGraph::Graph g;
    g.generateRandomGraphPrecise(n);

    vector<unsigned int> graphVerticesVector(g.size());
    for(auto v : g.getVertices())
        graphVerticesVector.push_back(v.first);

    BijectionFunction bj (graphVerticesVector);

    g.fill_in(bj);
}