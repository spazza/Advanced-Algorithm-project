#define BOOST_TEST_MODULE Lex_p

#include "Graph.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

BOOST_AUTO_TEST_CASE(Perfect_ordering) {
    vector<unsigned int> vertices = {1,2,3,4,5,6,7,8,9,10};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,3);
    g.addEdge(1,5);
    g.addEdge(2,6);
    g.addEdge(2,7);
    g.addEdge(3,5);
    g.addEdge(3,4);
    g.addEdge(3,9);
    g.addEdge(4,5);
    g.addEdge(4,9);
    g.addEdge(5,8);
    g.addEdge(5,9);
    g.addEdge(6,7);
    g.addEdge(6,10);
    g.addEdge(7,10);
    g.addEdge(8,9);
    g.addEdge(8,10);
    g.addEdge(9,10);

    vector<unsigned int> bij_vector = g.lex_p();

    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.edgeSize() == prev_edges);
}

BOOST_AUTO_TEST_CASE(Non_perfect_ordering) {
    vector<unsigned int> vertices = {1,2,3,4,5,6};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,3);
    g.addEdge(1,4);
    g.addEdge(2,3);
    g.addEdge(2,5);
    g.addEdge(3,6);
    g.addEdge(4,6);
    g.addEdge(5,6);

    vector<unsigned int> bij_vector = g.lex_p();

    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.edgeSize() != prev_edges);
    BOOST_TEST(g.edgeSize() == prev_edges + 3);
}