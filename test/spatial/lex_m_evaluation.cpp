#include "Graph.hpp"
#include <iostream>

using namespace std;

// Trivial program to test lex_m function
// Insert as first main parameter the number of elements in the graph.
// N.B. num_elements = num_vertices + num_edges

int main(int argc, char *argv[]) {
    unsigned int n = stoi(argv[1]);

    CustomGraph::Graph g;
    g.generateRandomGraphPrecise(n);

    g.lex_m();
}