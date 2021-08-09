#include "Graph.hpp"

#include <boost/test/unit_test.hpp>

using namespace CustomGraph;

// Test suite for fill-in function.

BOOST_AUTO_TEST_SUITE(Fill_in_tests)

// Test case explained in the paper 

BOOST_AUTO_TEST_CASE(Paper_example) {
    vector<unsigned int> vertices = {1,2,3,4,5,6};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,3);
    g.addEdge(1,4);
    g.addEdge(2,3);
    g.addEdge(2,5);
    g.addEdge(3,6);
    g.addEdge(4,6);
    g.addEdge(5,6);

    BijectionFunction bf(vertices);
    g.fill_in(bf);

    BOOST_TEST(g.getVertices()[3].isAdjacent(4));
    BOOST_TEST(g.getVertices()[4].isAdjacent(3));

    BOOST_TEST(g.getVertices()[3].isAdjacent(5));
    BOOST_TEST(g.getVertices()[5].isAdjacent(3));

    BOOST_TEST(g.getVertices()[4].isAdjacent(5));
    BOOST_TEST(g.getVertices()[5].isAdjacent(4));

    BOOST_TEST(g.size() == vertices.size());
    BOOST_TEST(g.edgeSize() == (unsigned int)10);
}

// Fill-in of a cycle graph, for each vertex an edge between the two neighbour is created

BOOST_AUTO_TEST_CASE(Cycle_graph) {
    vector<unsigned int> vertices = {7,11,5,9,20};
    CustomGraph::Graph g(vertices);

    g.addEdge(7,5);
    g.addEdge(7,11);
    g.addEdge(5,9);
    g.addEdge(11,20);
    g.addEdge(9,20);

    BijectionFunction bf(vertices);
    g.fill_in(bf);

    BOOST_TEST(g.getVertices()[11].isAdjacent(5));
    BOOST_TEST(g.getVertices()[5].isAdjacent(11));

    BOOST_TEST(g.getVertices()[5].isAdjacent(20));
    BOOST_TEST(g.getVertices()[20].isAdjacent(5));

    BOOST_TEST(g.size() == vertices.size());
    BOOST_TEST(g.edgeSize() == (unsigned int)7);
}

// Fill-in of a graph with a sink vertex, if the sink vertex is eliminated at first an edge among all its neighbours must be created.

BOOST_AUTO_TEST_CASE(Sink_vertex_graph) {
    vector<unsigned int> vertices = {4,6,9,10};
    CustomGraph::Graph g(vertices);

    g.addEdge(4,6);
    g.addEdge(4,9);
    g.addEdge(4,10);

    BijectionFunction bf(vertices);
    g.fill_in(bf);

    BOOST_TEST(g.getVertices()[6].isAdjacent(9));
    BOOST_TEST(g.getVertices()[9].isAdjacent(6));

    BOOST_TEST(g.getVertices()[6].isAdjacent(10));
    BOOST_TEST(g.getVertices()[10].isAdjacent(6));

    BOOST_TEST(g.getVertices()[9].isAdjacent(10));
    BOOST_TEST(g.getVertices()[10].isAdjacent(9));

    BOOST_TEST(g.size() == vertices.size());
    BOOST_TEST(g.edgeSize() == (unsigned int)6);
}

// Fill-in of a chain graph, no edge is created in that case.

BOOST_AUTO_TEST_CASE(Chain_graph) {
    vector<unsigned int> vertices = {5,9,1,41,3};
    CustomGraph::Graph g(vertices);

    g.addEdge(5,9);
    g.addEdge(9,1);
    g.addEdge(1,41);
    g.addEdge(41,3);

    BijectionFunction bf(vertices);
    g.fill_in(bf);

    BOOST_TEST(g.size() == vertices.size());
    BOOST_TEST(g.edgeSize() == (unsigned int)g.size() - 1);
}

BOOST_AUTO_TEST_SUITE_END()
