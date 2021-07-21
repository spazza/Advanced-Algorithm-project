#define BOOST_TEST_MODULE Graph_correctness

#include "Graph.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;
namespace bdata = boost::unit_test::data;

const unsigned int graph_dimension[] = {0, 1, 2, 3, 4, 32, 128, 256};

BOOST_DATA_TEST_CASE(Vertex_insertion, bdata::make(graph_dimension), n) {
    srand(time(NULL));
    Graph g_test;

    vector<unsigned int> test_vertices;
    for(unsigned int i = 0; i < n; ++i) {
        unsigned int temp_value = rand() % n;

        g_test.addVertex(temp_value);

        test_vertices.push_back(temp_value);
    }

    BOOST_TEST(g_test.size() == test_vertices.size());

    unsigned int i = 0;
    auto vertexIt = g_test.getVertices().begin();

    while(i < n) {
        BOOST_TEST((*vertexIt).value == test_vertices[i]);

        ++i;
        ++vertexIt;
    }
}

BOOST_DATA_TEST_CASE(Edge_insertion, bdata::make(graph_dimension), n) {
    srand(time(NULL));
    Graph g_test;

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

        src_vertices[i] = src_vertex;
        dst_vertices[i] = dst_vertex;

        g_test.addEdge(src_vertex, dst_vertex);
    }

    for(unsigned int i = 0; i < num_distinct_edges; ++i)
        if(g_test.isInTheGraph(src_vertices[i]) && g_test.isInTheGraph(dst_vertices[i]))
            for(auto vertexIt = g_test.getVertices().begin(); vertexIt != g_test.getVertices().end(); ++vertexIt)
                if((*vertexIt).value == src_vertices[i])
                    BOOST_TEST((*vertexIt).isAdjacent(dst_vertices[i]));
}

