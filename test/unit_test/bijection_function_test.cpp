#include "BijectionFunction.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <random>
#include <unordered_set>

using namespace boost;
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(Bijection_function_tests)

const unsigned vector_dim[] = {0, 1, 2, 4, 8, 64, 512};

// Test the correct assignment of values to the bijection.
// Both the direct and in the inverse way are checked.

BOOST_DATA_TEST_CASE(Bijection_function_test, bdata::make(vector_dim), n) {
    unordered_set<unsigned int> unique_vertices;

    // Random generated vertices
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr_vertices(1, n);

    for(unsigned int i = 0; i < n; ++i) 
        unique_vertices.insert(distr_vertices(gen));
    
    // Copy vertices in a vector
    vector<unsigned int> vertices(unique_vertices.begin(), unique_vertices.end());

    BijectionFunction b(vertices);  

    // Check both assignments
    for(unsigned int i = 0; i < vertices.size(); ++i) {
        BOOST_TEST(b.alpha(i) == vertices[i]);
        BOOST_TEST(b.alphaInverse(vertices[i]) == i);
    }
}

BOOST_AUTO_TEST_SUITE_END()