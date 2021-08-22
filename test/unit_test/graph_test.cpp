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

// Test the correct insertion in the graph of new vertices.

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

// Test the correct insertion in the graph of a new edge.

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

// Test the fact that in the graph there cannot be duplicated vertices.

BOOST_AUTO_TEST_CASE(Remove_duplicated_vertices) {
    unsigned int duplicated_vertices = 5;
    CustomGraph::Graph g_test;

    for(unsigned int i = 0; i < duplicated_vertices; ++i) {
        g_test.addVertex(1);
        g_test.addVertex(2);
        g_test.addVertex(3);
    }

    BOOST_TEST(g_test.size() == (unsigned int) 3);
}

// In the graph auto-ring are not allowed.

BOOST_AUTO_TEST_CASE(No_auto_ring) {
    CustomGraph::Graph g_test;
    g_test.addVertex(1);
    g_test.addVertex(2);
    g_test.addEdge(1,1);
    g_test.addEdge(2,2);

    BOOST_TEST(g_test.edgeSize() == (unsigned int)0);
    BOOST_TEST(!g_test.getVertices()[1].isAdjacent(1));
}

// Check if the graph is connected or not.

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

// Check the correct elimination of a vertex 

BOOST_AUTO_TEST_CASE(Delete_vertex) {
    vector<unsigned int> vertices = {1,7,4,3,11};
    CustomGraph::Graph g(vertices);

    g.addEdge(1,7);
    g.addEdge(1,4);
    g.addEdge(1,3);
    g.addEdge(7,3);
    g.addEdge(7,11);
    g.addEdge(4,11);
    g.addEdge(3,11);

    g.deleteVertex(1);

    // Three edges should have been removed
    BOOST_TEST(g.size() == vertices.size()-1);
    BOOST_TEST(g.edgeSize() == (unsigned int)4);
    for(auto v : g.getVertices()) 
        BOOST_TEST(!(v.second.isAdjacent(1)));

    g.deleteVertex(7);

    BOOST_TEST(g.size() == vertices.size()-2);
    BOOST_TEST(g.edgeSize() == (unsigned int)2);
    for(auto v : g.getVertices()) 
        BOOST_TEST(!(v.second.isAdjacent(7)));
}

const unsigned int random_graph_dimension[] = {8, 16, 32, 128, 256, 1024};

// Check the correct random generation of graphs and that the main graph properites are verified.

BOOST_DATA_TEST_CASE(Graph_random_creation, bdata::make(random_graph_dimension), n) {
    CustomGraph::Graph g;
    g.generateRandomGraph(n);

    BOOST_TEST(g.isConnected());
    BOOST_TEST(g.size() == n);

    g.clear();

    g.generateRandomGraphPrecise(n);

    BOOST_TEST(g.isConnected());
}

BOOST_AUTO_TEST_SUITE_END()