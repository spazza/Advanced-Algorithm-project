#include "Graph.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>


BOOST_AUTO_TEST_SUITE(Lex_m_test)

// Test case explained in the paper that shows a minimal ordering.

BOOST_AUTO_TEST_CASE(Paper_example_minimal_ordering) {
    vector<unsigned int> vertices = {1,2,3,4,5,6,7,8,9};
    reverse(vertices.begin(), vertices.end());
    CustomGraph::Graph g(vertices);

    g.addEdge(1,2);
    g.addEdge(1,5);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(2,6);
    g.addEdge(3,7);
    g.addEdge(4,5);
    g.addEdge(4,6);
    g.addEdge(4,8);
    g.addEdge(5,8);
    g.addEdge(6,7);
    g.addEdge(6,9);
    g.addEdge(7,9);
    g.addEdge(8,9);

    unsigned int prev_edges = g.edgeSize();
    vector<unsigned int>  bij_vector = g.lex_m();

    BOOST_TEST(g.edgeSize() == prev_edges + 6);
}

// Test case of a graph that is already triangulated and so there is no need to add edges.
// in the cycle. Therefore, lex_m should produce a minimal ordering without add anything. 

BOOST_AUTO_TEST_CASE(Unique_chord_graph) {
    vector<unsigned int> vertices = {1,2,3,4,5};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(5,1);
    g.addEdge(2,4);
    g.addEdge(2,5);

    unsigned int prev_edges = g.edgeSize();
    vector<unsigned int> bij_vector = g.lex_m();

    BOOST_TEST(g.edgeSize() == prev_edges);
}

// Test case of a graph where each added edge is a unique chord of a 4-cycle.
// In that case, lex_m should produce edges such that for each vertex in a cycle with k > 3
// there is an edge linking two non-consecutive vertices.

BOOST_AUTO_TEST_CASE(Non_unique_chord_graph) {
    vector<unsigned int> vertices = {1,2,3,4,5,6,7};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,4);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(4,6);
    g.addEdge(5,7);
    g.addEdge(6,7);

    unsigned int prev_edges = g.edgeSize();
    vector<unsigned int> bij_vector = g.lex_m();

    BOOST_TEST(g.edgeSize() == prev_edges + 2);
    BOOST_TEST(g.getVertices()[5].isAdjacent(6));
    BOOST_TEST(g.getVertices()[2].isAdjacent(3));
}

// Lex_m of a chain graph, it should always produce a minimal ordering without adding any edge.

BOOST_AUTO_TEST_CASE(Chain_graph) {
    vector<unsigned int> vertices = {4,1,7,9,15};
    CustomGraph::Graph g(vertices);

    g.addEdge(4,1);
    g.addEdge(1,7);
    g.addEdge(7,9);
    g.addEdge(9,15);

    unsigned int prev_edges = g.edgeSize();
    vector<unsigned int> bij_vector = g.lex_m();

    BOOST_TEST(g.edgeSize() == prev_edges);
}

// Lex_m of a graph with a sink vertex, it should always produce a minimal ordering without adding any edge.

BOOST_AUTO_TEST_CASE(Sink_vertex_graph) {
    vector<unsigned int> vertices = {1,2,3,4};
    CustomGraph::Graph g1(vertices);

    g1.addEdge(1,2);
    g1.addEdge(1,3);
    g1.addEdge(1,4);
    g1.addEdge(1,5);

    unsigned int prev_edges = g1.edgeSize();
    vector<unsigned int> bij_vector = g1.lex_m();

    BOOST_TEST(g1.edgeSize() == prev_edges);

    reverse(vertices.begin(), vertices.end());
    CustomGraph::Graph g2(vertices);

    g1.addEdge(1,2);
    g1.addEdge(1,3);
    g1.addEdge(1,4);
    g1.addEdge(1,5);

    prev_edges = g2.edgeSize();
    bij_vector = g2.lex_m();

    BOOST_TEST(g2.edgeSize() == prev_edges);
}


BOOST_AUTO_TEST_SUITE_END()