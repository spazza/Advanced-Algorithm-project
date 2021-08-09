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

/**
 * @brief auxiliary structure that allows to create undirected connected graphs that will be used for testing.
 * It exploits the Erdos - Renyi model to generate graphs in a random manner, to obtain this solution a BOOST
 * graph library has been used.
 */
struct RandomGraphGenerator {
    /**
     * @brief Construct a new Random Graph Generator object that will have a number of vertices specified in the 
     * first parameter.
     * @param num_vertices integer that specifies the number of vertices of the random graph.
     */
    RandomGraphGenerator(unsigned int num_vertices) ;

    /**
     * @brief Generate the random graph.
     */
    void generate();

    /**
     * @brief Get the Vertices that have been generated randomly.
     * @return vector<unsigned int> that contains the vertices.
     */
    vector<unsigned int>& getVertices();

    /**
     * @brief Get the source of the vertices that have been generated randomly.
     * @return vector<unsigned int> that contains the source of the edges.
     */
    vector<unsigned int>& getEdgesSrc();

    /**
     * @brief Get the destination of the vertices that have been generated randomly.
     * @return vector<unsigned int> that contains the destination of the edges.
     */
    vector<unsigned int>& getEdgesDst();

private:

    /**
     * @brief Number of vertices in the graph.
     */
    unsigned int num_vertices;

    /**
     * @brief Vertices generated after the call of generate function.
     */
    vector<unsigned int> vertices;

    /**
     * @brief Sources of the edges created by the generate function.
     * 
     */
    vector<unsigned int> src_edges;

    /**
     * @brief Destinations of the edges created by the generate function.
     * 
     */
    vector<unsigned int> dst_edges;
};

#endif