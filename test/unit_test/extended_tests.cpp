#include "Graph.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

using namespace boost;
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(Extended_tests)

const unsigned int graph_dimension[] = {8, 16, 64, 256, 1024, /*4096*/};

// Random extended test for fill_in function
// The fill_in on the random graph is executed and then each node is eliminated, the procedure is correct 
// if all the nodes adjacent to the eliminated one are pairwise adjacent.

BOOST_DATA_TEST_CASE(Fill_in_random_test, bdata::make(graph_dimension), n) {
    CustomGraph::Graph g;
    g.generateRandomGraphPrecise(n);

    vector<unsigned int> graph_vertices = g.getVerticesKeys();
    BijectionFunction bj(graph_vertices);
    g.fill_in(bj);

    // Delete one node at time
    for(unsigned int i = 0; i < graph_vertices.size(); ++i) {
        std::unordered_set<unsigned int> adj_vertices = g.getVertices()[bj.alpha(i)].getAdjVertices();
        g.deleteVertex(bj.alpha(i));
        
        // Check if the neighbours are pairwise adjacent.
        for(auto v : adj_vertices)
            for(auto w : adj_vertices)
                if(v != w)
                    BOOST_TEST(g.getVertices()[v].isAdjacent(w));
    }
}

// Random extended test for lex_p function
// Lex_p function is executed and returns an ordering that may be perfect, then I apply the fill_in function
// and if it does not add any edge it means that the ordering is perfect. In that case, I check the vertex deletion
// and if all the adjacent vertices to the deleted one are pairwise adjacent.

BOOST_DATA_TEST_CASE(Lex_p_random_test, bdata::make(graph_dimension), n) {
    CustomGraph::Graph g;
    g.generateRandomGraphPrecise(n);

    unsigned int prev_graph_edges_size = g.edgeSize();
    vector<unsigned int> lex_p_vertices = g.lex_p();

    // Apply the fill-in
    BijectionFunction bj(lex_p_vertices);
    g.fill_in(bj);

    // If none edge has been added using the fill-in function, the ordering is perfect
    if(g.edgeSize() == prev_graph_edges_size) {
        //cout << "A perfect ordering has been found (vertices = " << g.size() << " edges = " << g.edgeSize() << ")" << endl;

        // Additional check, deleting a node all its neighbours must be pairwise adjacent.
        for(unsigned int i = 0; i < lex_p_vertices.size(); ++i) {
            std::unordered_set<unsigned int> adj_vertices = g.getVertices()[bj.alpha(i)].getAdjVertices();
            g.deleteVertex(bj.alpha(i));

            // Check if the neighbours are pairwise adjacent.
            for(auto v : adj_vertices)
                for(auto w : adj_vertices)
                    if(v != w)
                        BOOST_TEST(g.getVertices()[v].isAdjacent(w));
        }
    }
}

// Random extended test for lex_m function
// Lex_m function is executed and returns a minimal ordering, in some cases it may be perfect.
// Then I check the node deletion in order to verify that the adjacent vertices to the deleted one
// are pairwise adjacent.

BOOST_DATA_TEST_CASE(Lex_m_random_test, bdata::make(graph_dimension), n) {
    CustomGraph::Graph g;
    g.generateRandomGraphPrecise(n);

    vector<unsigned int> lex_m_vertices = g.lex_m();

    BijectionFunction bj(lex_m_vertices);
    g.fill_in(bj);

    // Deleting a node all its neighbours must be pairwise adjacent.
    for(unsigned int i = 0; i < lex_m_vertices.size(); ++i) {
        std::unordered_set<unsigned int> adj_vertices = g.getVertices()[bj.alpha(i)].getAdjVertices();
        g.deleteVertex(bj.alpha(i));

        // Check if the neighbours are pairwise adjacent.
        for(auto v : adj_vertices)
            for(auto w : adj_vertices)
                if(v != w && g.isInside(v) && g.isInside(w))
                    BOOST_TEST(g.getVertices()[v].isAdjacent(w));
    }  
}

BOOST_AUTO_TEST_SUITE_END()