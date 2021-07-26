#ifndef RANDOM_GRAPH_GENERATOR_H_
#define RANDOM_GRAPH_GENERATOR_H_

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>

#include <vector>
#include <random>

using namespace std;

typedef boost::adjacency_list<> Graph;
typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;

struct RandomGraphGenerator {
    RandomGraphGenerator(unsigned int num_vertices) ;

    void generate();
    vector<unsigned int> getVertices();
    vector<unsigned int> getEdgesSrc();
    vector<unsigned int> getEdgesDst();

private:
    unsigned int num_vertices;
    vector<unsigned int> vertices;
    vector<unsigned int> src_edges;
    vector<unsigned int> dst_edges;
};

#endif