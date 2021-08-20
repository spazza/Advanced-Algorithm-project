#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Sets.hpp"

using namespace boost;
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(Sets_tests)

const unsigned int set_dimension[] = {0, 1, 2, 4, 10, 100};

// Check the correct initialization of the Set structure
// In particular the position of the inside vertices.

BOOST_DATA_TEST_CASE(Sets_initilization, bdata::make(set_dimension), n) {
    srand(time(NULL));
    std::unordered_set<unsigned int> vertices(n);

    for(unsigned int i = 0; i < n; ++i)
        vertices.insert(rand() % set_dimension[5]);
    
    Sets sets(vertices);

    BOOST_TEST(sets.size() == vertices.size());

    for(auto it = vertices.begin(); it != vertices.end(); ++it) {
        std::unordered_set<unsigned int> inner_set = sets.getVertexPosition(*it)->set_values;
        bool result = inner_set.find(*it) != inner_set.end();
        BOOST_TEST(result);
    }
}

// Test the removal of a vertex in the set.
// Only the position must be null.

BOOST_AUTO_TEST_CASE(Remove_test) {
    std::unordered_set<unsigned int> vertices = {1, 2, 3, 4};
    Sets sets(vertices);

    sets.remove(1);

    BOOST_TEST(sets.size() == vertices.size());
    BOOST_TEST(sets.getVertexPosition(1) != nullptr);
}

// Test the definitive removal of a vertex in the set.
// Position have to be null and set size have to decrease.

BOOST_AUTO_TEST_CASE(Remove_definitely_test) {
    std::unordered_set<unsigned int> vertices = {1, 2, 3, 4};
    Sets sets(vertices);

    sets.removeDefinitely(1);

    BOOST_TEST(sets.size() == vertices.size()-1);
    BOOST_TEST(sets.getVertexPosition(1) == nullptr);
}

// Add a new set in a new position inside the structure.

BOOST_AUTO_TEST_CASE(Add_set_test) {
    std::unordered_set<unsigned int> vertices = {1, 2, 3, 4};
    Sets sets(vertices);

    sets.remove(1);

    Cell *removed_node_cell = sets.getVertexPosition(1);

    sets.addSet(removed_node_cell, 1);

    BOOST_TEST(vertices.size() == sets.size());
    BOOST_TEST(removed_node_cell != sets.getVertexPosition(1));
}

BOOST_AUTO_TEST_SUITE_END()