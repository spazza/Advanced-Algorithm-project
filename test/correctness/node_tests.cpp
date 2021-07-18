#define BOOST_TEST_MODULE Graph_correctness

#include "Graph.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

using namespace boost;
namespace bdata = boost::unit_test::data;

/**
 * Correct node insertion 
 **/

const int node_test_values[][] = {{1, 2, 3, 4, 5},
                                  {1, 2, 3}};

BOOST_DATA_TEST_CASE(Node_insertion_test, bdata::make(node_list), value){
    Graph g_test;

    for(auto v : value) {
        Node n(v);
        g_test.addNode(n);
    }

}



