#include "Graph.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>


BOOST_AUTO_TEST_SUITE(Lex_m_tests)

BOOST_AUTO_TEST_CASE(SortByLabelTest) {
    CustomGraph::Graph g;

    vector<unsigned int> vertices = {3,5,1,7,9,15};
    std::unordered_map<unsigned int, float> label = {{3, 1.5}, {5, 2.5}, {1, 1.5}, {7, 3.5}, {9, 1.5}, {15, 2.5}};
    unsigned int k;

    g.sortByLabel(vertices, label, &k);

    vector<unsigned int > correct_ordering = {7,5,15,3,9,1};
    std::unordered_map<unsigned int, float> correct_labels = {{7,3}, {5,2}, {15,2}, {1,1}, {3,1}, {9,1}};
    unsigned int correct_k = 3;

    for(unsigned int i = 0; i < vertices.size(); ++i) {
        BOOST_TEST(vertices[i] == correct_ordering[i]);
        BOOST_TEST(label[correct_ordering[i]] == correct_labels[correct_ordering[i]]);
    }

    BOOST_TEST(k == correct_k);
}

BOOST_AUTO_TEST_CASE(Lex_m_trivial_test) {
    vector<unsigned int> vertices = {1,2,3,4,5,6,7,8,9};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,2);
    g.addEdge(1,5);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(2,6);
    g.addEdge(3,7);
    g.addEdge(4,6);
    g.addEdge(4,8);
    g.addEdge(5,8);
    g.addEdge(6,7);
    g.addEdge(6,9);
    g.addEdge(7,9);
    g.addEdge(8,9);

    list<pair<unsigned int, unsigned int>>  bij_vector = g.lex_m();    
}


BOOST_AUTO_TEST_SUITE_END()