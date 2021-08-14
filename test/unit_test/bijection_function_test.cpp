#include "Graph.hpp"

#include <boost/test/unit_test.hpp>

using namespace CustomGraph;

BOOST_AUTO_TEST_SUITE(Bijection_function_tests)

BOOST_AUTO_TEST_CASE(Bijection_function_test) {
    vector<unsigned int> unorderedSet = {5, 11, 9, 23};

    BijectionFunction b(unorderedSet);  

    for(unsigned int i = 0; i < unorderedSet.size(); ++i) {
        BOOST_TEST(b.alpha(i) == unorderedSet[i]);
        BOOST_TEST(b.alphaInverse(unorderedSet[i]) == i);
    }
}

BOOST_AUTO_TEST_SUITE_END()