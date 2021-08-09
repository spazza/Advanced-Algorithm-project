#include "Graph.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>


BOOST_AUTO_TEST_SUITE(Lex_p_tests)

// Test case explained in the paper that shows a perfect ordering.

BOOST_AUTO_TEST_CASE(Paper_example_perfect_ordering) {
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

    unsigned int prev_vertices = g.size();
    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.size() == prev_vertices);
    BOOST_TEST(g.edgeSize() == prev_edges);
}

// Test case explained in the paper that shows a non-perfect ordering.

BOOST_AUTO_TEST_CASE(Paper_example_non_perfect_ordering) {
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

    unsigned int prev_vertices = g.size();
    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.size() == prev_vertices);
    BOOST_TEST(g.edgeSize() != prev_edges);
}

// Lex_p of a chain graph, it should be always perfect.

BOOST_AUTO_TEST_CASE(Chain_graph) {
    vector<unsigned int> vertices = {1,2,3,4,5};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,4);
    g.addEdge(4,5);

    vector<unsigned int> bij_vector = g.lex_p();

    unsigned int prev_vertices = g.size();
    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.size() == prev_vertices);
    BOOST_TEST(g.edgeSize() == prev_edges);
}

// Lex_p of a graph with a sink vertex. The ordering starts from the leaf nodes and it is perfect.

BOOST_AUTO_TEST_CASE(Sink_vertex_graph) {
    vector<unsigned int> vertices = {7,5,2,11};
    CustomGraph::Graph g(vertices);

    g.addEdge(7,5);
    g.addEdge(7,2);
    g.addEdge(7,11);

    vector<unsigned int> bij_vector = g.lex_p();

    unsigned int prev_vertices = g.size();
    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.size() == prev_vertices);
    BOOST_TEST(g.edgeSize() == prev_edges);
}

// Lex_p of a triangulated graph, an ordering of a triangulated graph should be always perfect.

BOOST_AUTO_TEST_CASE(Triangulated_graph) {
    vector<unsigned int> vertices = {3,6,1,5,12};
    CustomGraph::Graph g(vertices);

    g.addEdge(3,6);
    g.addEdge(6,1);
    g.addEdge(1,5);
    g.addEdge(5,12);
    g.addEdge(12,3);
    g.addEdge(3,1);
    g.addEdge(1,12);

    vector<unsigned int> bij_vector = g.lex_p();

    unsigned int prev_vertices = g.size();
    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.size() == prev_vertices);
    BOOST_TEST(g.edgeSize() == prev_edges);
}

//Lex_p of a non-triangulated graph, in that case it shouldn't be perfect

BOOST_AUTO_TEST_CASE(Non_triangulated_graph) {
    vector<unsigned int> vertices = {3,6,1,5,12};
    CustomGraph::Graph g(vertices);

    g.addEdge(3,6);
    g.addEdge(6,1);
    g.addEdge(1,5);
    g.addEdge(5,12);
    g.addEdge(12,3);

    vector<unsigned int> bij_vector = g.lex_p();

    unsigned int prev_vertices = g.size();
    unsigned int prev_edges = g.edgeSize();
    BijectionFunction bf(bij_vector);
    g.fill_in(bf);

    BOOST_TEST(g.size() == prev_vertices);
    BOOST_TEST(g.edgeSize() != prev_edges);
}   

BOOST_AUTO_TEST_SUITE_END()