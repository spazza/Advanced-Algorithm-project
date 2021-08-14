#include "Graph.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;
using namespace CustomGraph;
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(Graph_tests)

const unsigned int graph_dimension[] = {0, 2, 3, 4, 32, 128, 256};

BOOST_DATA_TEST_CASE(Vertex_insertion, bdata::make(graph_dimension), n) {
    srand(time(NULL));
    CustomGraph::Graph g_test;

    vector<unsigned int> test_vertices;
    for(unsigned int i = 0; i < n; ++i) {
        g_test.addVertex(i);
        test_vertices.push_back(i);
    }

    BOOST_TEST(g_test.size() == test_vertices.size());

    for(unsigned int i = 0; i < test_vertices.size(); ++i) 
        BOOST_TEST(g_test.getVertices()[test_vertices[i]].value == test_vertices[i]);
    
}

BOOST_DATA_TEST_CASE(Edge_insertion, bdata::make(graph_dimension), n) {
    srand(time(NULL));
    CustomGraph::Graph g_test;

    for(unsigned int i = 0; i < n; ++i) {
        unsigned int temp_value = rand() % n;

        g_test.addVertex(temp_value);
    }

    srand(time(NULL));
    unsigned int num_distinct_edges = n * 4;

    vector<unsigned int> src_vertices, dst_vertices;
    src_vertices.resize(num_distinct_edges);
    dst_vertices.resize(num_distinct_edges);

    for(unsigned int i = 0; i < num_distinct_edges; ++i) {
        unsigned int src_vertex = rand() % n;
        unsigned int dst_vertex = rand() % n;
    
        while(src_vertex == dst_vertex)
            dst_vertex = rand() % n;
        
        src_vertices[i] = src_vertex;
        dst_vertices[i] = dst_vertex;

        g_test.addEdge(src_vertex, dst_vertex);
    }

    for(unsigned int i = 0; i < num_distinct_edges; ++i)
        if(g_test.isInside(src_vertices[i]) && g_test.isInside(dst_vertices[i]))
            for(auto vertexIt = g_test.getVertices().begin(); vertexIt != g_test.getVertices().end(); ++vertexIt)
                if((*vertexIt).second.value == src_vertices[i])
                    BOOST_TEST((*vertexIt).second.isAdjacent(dst_vertices[i]));
}

BOOST_AUTO_TEST_CASE(Remove_duplicated_nodes) {
    unsigned int duplicated_nodes = 5;
    CustomGraph::Graph g_test;

    for(unsigned int i = 0; i < duplicated_nodes; ++i) {
        g_test.addVertex(1);
        g_test.addVertex(2);
        g_test.addVertex(3);
    }

    BOOST_TEST(g_test.size() == (unsigned int) 3);
}

BOOST_AUTO_TEST_CASE(No_auto_ring) {
    CustomGraph::Graph g_test;
    g_test.addVertex(1);
    g_test.addEdge(1,1);

    BOOST_TEST(g_test.edgeSize() == (unsigned int)0);
    BOOST_TEST(!g_test.getVertices()[1].isAdjacent(1));
}

BOOST_AUTO_TEST_CASE(Connected_graph) {
    CustomGraph::Graph g_test;

    g_test.addVertex(1);
    g_test.addVertex(2);
    g_test.addVertex(3);

    g_test.addEdge(1,2);
    g_test.addEdge(1,3);

    BOOST_TEST(g_test.isConnected());
    
    g_test.addVertex(4);

    BOOST_TEST(!g_test.isConnected());

    g_test.addEdge(3,4);

    BOOST_TEST(g_test.isConnected());

    g_test.addVertex(5);

    BOOST_TEST(!g_test.isConnected());
}

const unsigned int random_graph_dimension[] = {2, 4, 8, 128, 256, 1024};

BOOST_DATA_TEST_CASE(Graph_random_creation, bdata::make(random_graph_dimension), n) {
    CustomGraph::Graph g;
    g.generateRandomGraph(n);

    BOOST_TEST(g.isConnected());
    BOOST_TEST(g.size() == n);
}


BOOST_AUTO_TEST_SUITE_END()