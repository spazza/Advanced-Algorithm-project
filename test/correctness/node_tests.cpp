#define BOOST_TEST_MODULE Graph_correctness

#include "Graph.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <algorithm>

using namespace boost;
namespace bdata = boost::unit_test::data;

const unsigned int graph_dimension[] = {0, 1, 2, 3, 4, 8, 16, 256};

/**
 * @brief Boost data test case object that checks if the nodes are correctly inserted in the
 * graph. The dimension of the graph is checked first and then value of each node.
 */
BOOST_DATA_TEST_CASE(Node_insertion_test, bdata::make(graph_dimension), test_graph_dim){
    Graph g_test;

    // Nodes generation and initialization
    Node *temp_node_ptr;
    for(unsigned int i = 0; i < test_graph_dim; ++i) {
        temp_node_ptr = new Node(i);
        g_test.addNode(temp_node_ptr);
    }

    BOOST_TEST(g_test.getDimension() == test_graph_dim);

    // Nodes check
    for(unsigned int i = 0; i < test_graph_dim; ++i) {
        BOOST_TEST(g_test.getNode(i) != nullptr);
        BOOST_TEST(g_test.getNode(i)->getValue() == i);
    }
}

/**
 * @brief Boost data test case object that checks if the edges are correctly inserted
 * and if they are able to connect all the nodes in the graph.
 * The graph is fully connected, each node is connected to all the other nodes. 
 */
BOOST_DATA_TEST_CASE(Edge_insertion_test, bdata::make(graph_dimension), test_graph_dim) {
    Graph g_test;

    Node *temp_node_ptr;
    for(unsigned int i = 0; i < test_graph_dim; ++i) {
        temp_node_ptr = new Node(i);
        g_test.addNode(temp_node_ptr);
        for(unsigned int j = 0; j < i; ++j)
            g_test.addEdge(temp_node_ptr, g_test.getNode(j));
    }

    for(unsigned int i = 0; i < test_graph_dim; ++i)
        
        for(unsigned int j = 0; j < test_graph_dim; ++j) {
            // No auto-rings do not check the node with itself
            if(i == j)
                continue;
            std::vector<Node*> *adj_nodes = g_test.getNode(i)->getAdjacentNodes();
            bool result = std::find(adj_nodes->begin(), adj_nodes->end(), g_test.getNode(j)) != adj_nodes->end();
            BOOST_TEST(result);
        }
}

/**
 * @brief Boost auto test case object to check the absence of edges that
 * start from a node and terminate on the same node.
 */
BOOST_AUTO_TEST_CASE(No_auto_ring_test) {
    Graph g_test;
    Node *node_ptr = new Node(1);
    g_test.addNode(node_ptr);

    Node *same_node_ptr = new Node(1);
    g_test.addNode(same_node_ptr);

    g_test.addEdge(node_ptr, same_node_ptr);

    std::vector<Node*> *adj_nodes = node_ptr->getAdjacentNodes();
    bool result = std::find(adj_nodes->begin(), adj_nodes->end(), same_node_ptr) != adj_nodes->end();
    BOOST_TEST(!result);
}

/**
 * @brief Boost auto test case object to check the absence of duplicate
 * edges between two nodes.
 */
BOOST_AUTO_TEST_CASE(No_duplicated_edges_test) {
    Graph g_test;
    Node *node1_ptr = new Node(1);
    Node *node2_ptr = new Node(2);
    g_test.addNode(node1_ptr);
    g_test.addNode(node2_ptr);

    g_test.addEdge(node1_ptr, node2_ptr);
    g_test.addEdge(node1_ptr, node2_ptr);
    g_test.addEdge(node2_ptr, node1_ptr);

    std::vector<Node*> *adj_nodes_node1 = node1_ptr->getAdjacentNodes();
    std::vector<Node*> *adj_nodes_node2 = node2_ptr->getAdjacentNodes();

    BOOST_TEST(adj_nodes_node1->size() == (unsigned int)1);
    BOOST_TEST(adj_nodes_node2->size() == (unsigned int)1);
}