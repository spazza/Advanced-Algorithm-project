#define BOOST_TEST_MODULE Sets_test

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Sets.hpp"
#include <iostream>

using namespace boost;
namespace bdata = boost::unit_test::data;

const unsigned int set_dimension[] = {0,1,2,4,10,100};

BOOST_DATA_TEST_CASE(Sets_initilization, bdata::make(set_dimension), n) {
    srand(time(NULL));
    unordered_set<unsigned int> vertices(n);

    for(unsigned int i = 0; i < n; ++i)
        vertices.insert(rand() % set_dimension[5]);
    
    Sets sets(vertices);

    BOOST_TEST(sets.size() == vertices.size());

    for(auto it = vertices.begin(); it != vertices.end(); ++it) {
        unordered_set<unsigned int> inner_set = sets.getVertexPosition(*it)->set_values;
        bool result = inner_set.find(*it) != inner_set.end();
        BOOST_TEST(result);
    }
}

BOOST_AUTO_TEST_CASE(Remove_test) {
    unordered_set<unsigned int> vertices = {1, 2, 3, 4};
    Sets sets(vertices);

    sets.remove(1);

    BOOST_TEST(sets.size() == vertices.size());
    BOOST_TEST(sets.getVertexPosition(1) != nullptr);
}

BOOST_AUTO_TEST_CASE(Remove_definitely_test) {
    unordered_set<unsigned int> vertices = {1, 2, 3, 4};
    Sets sets(vertices);

    sets.removeDefinitely(1);

    BOOST_TEST(sets.size() == vertices.size()-1);
    BOOST_TEST(sets.getVertexPosition(1) == nullptr);
}

BOOST_AUTO_TEST_CASE(Add_set_test) {
    unordered_set<unsigned int> vertices = {1, 2, 3, 4};
    Sets sets(vertices);

    sets.remove(1);

    Cell *removed_node_cell = sets.getVertexPosition(1);

    sets.addSet(removed_node_cell, 1);

    BOOST_TEST(vertices.size() == sets.size());
    BOOST_TEST(removed_node_cell != sets.getVertexPosition(1));
}
