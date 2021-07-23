//#define BOOST_TEST_MODULE Bijection_function

#include "Graph.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

BOOST_AUTO_TEST_CASE(Bijection_function_test) {
    vector<unsigned int> unorderedSet = {5, 11, 9, 23};

    BijectionFunction b(unorderedSet);  

    for(unsigned int i = 0; i < unorderedSet.size(); ++i) {
        BOOST_TEST(b.alpha(i) == unorderedSet[i]);
        BOOST_TEST(b.alphaInverse(unorderedSet[i]) == i);
    }
}