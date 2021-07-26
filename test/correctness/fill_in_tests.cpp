//#define BOOST_TEST_MODULE Fill_in

#include "Graph.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

using namespace CustomGraph;

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

BOOST_AUTO_TEST_CASE(Sink_vertex_graph) {
    vector<unsigned int> vertices = {4,6,9,10};
    CustomGraph::Graph g(vertices);

    g.addEdge(4,6);
    g.addEdge(4,9);
    g.addEdge(9,10);

    BijectionFunction bf(vertices);
    g.fill_in(bf);

    BOOST_TEST(g.getVertices()[6].isAdjacent(9));
    BOOST_TEST(g.getVertices()[9].isAdjacent(6));

    BOOST_TEST(g.size() == vertices.size());
    BOOST_TEST(g.edgeSize() == (unsigned int)4);
}

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
    BOOST_TEST(g.edgeSize() == (unsigned int)4);
}


