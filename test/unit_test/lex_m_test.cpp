#include "Graph.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>


BOOST_AUTO_TEST_SUITE(Lex_m_test)

BOOST_AUTO_TEST_CASE(Lex_m_trivial_test) {
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

    vector<unsigned int>  bij_vector = g.lex_m();
    
    list<pair<unsigned int, unsigned int>> expected_added_pairs = {{2,5}, {3,4}, {3,5}, {3,6} };
}


BOOST_AUTO_TEST_SUITE_END()