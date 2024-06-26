#include "CustomRadixSort.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <random>

using namespace std;
using namespace boost;
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(Custom_radix_sort_trivial_test)

// Trivial test case to check correct ordering and correct label assignment.

BOOST_AUTO_TEST_CASE(SortByLabelTest) {
    vector<pair<unsigned int, float>> vertices_and_labels = {{3, 1.5}, {5, 2.5}, {1, 1.5}, {7, 3.5}, {9, 1.5}, {15, 2.5}};
    unsigned int k = CustomRadixSort::sortByLabel(vertices_and_labels);

    vector<pair<unsigned int, float>> correct_ordering = {{7,3}, {15,2}, {5,2}, {9,1}, {1,1}, {3,1}};
    unsigned int correct_k = 3;

    for(unsigned int i = 0; i < vertices_and_labels.size(); ++i) {
        BOOST_TEST(vertices_and_labels[i].first == correct_ordering[i].first);
        BOOST_TEST(vertices_and_labels[i].second == correct_ordering[i].second);
    }

    BOOST_TEST(k == correct_k);
}


const unsigned int radix_sort_values[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 4096};

// Check that the ordering generated from random values and labels is correct.
// Each vertex is compared with the successive after the execution of function sortByLabel, and its position
// must be coherent with its label value.

BOOST_DATA_TEST_CASE(Correct_ordering, bdata::make(radix_sort_values), n) {
    // Random generator stuff
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr_vertices(1, n);
    uniform_int_distribution<> distr_label(1, 10);

    // To guarantee uniqueness of vertices they are stored in an unordered_set and then copied in a vector
    unordered_set<unsigned int> unique_vertices;
    unordered_map<unsigned int, float> label;

    // Random vertex and label generation
    for(unsigned int i = 0; i < n; ++i) {
        unsigned int random_vertex = distr_vertices(gen);
        unsigned int random_label = distr_label(gen);

        label[random_vertex] = random_label;
        unique_vertices.insert(random_vertex);
    }

    vector<pair<unsigned int, float>> vertices_and_labels(unique_vertices.size());
    unsigned int i = 0;
    for(auto v = unique_vertices.begin(); v != unique_vertices.end(); ++v) {
        vertices_and_labels[i] = make_pair(*v, label[*v]);
        i++;
    } 
        
    CustomRadixSort::sortByLabel(vertices_and_labels);
    
    // The label of each vertex must be greater or equal than the label of the successive one.
    for(unsigned int i = 0; i < vertices_and_labels.size()-1; i++)
        BOOST_TEST(vertices_and_labels[i].second >= vertices_and_labels[i+1].second);
}

// Check if the number of labels generated by the sortByLabel function and their values are correct.

BOOST_DATA_TEST_CASE(Correct_label_number, bdata::make(radix_sort_values), n) {
    // Random generator stuff
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr_label(1, 100);

    unordered_set<unsigned int> different_labels;
    vector<pair<unsigned int, float>> vertices_and_labels(n);

    // Random vertex and label generation
    for(unsigned int i = 0; i < n; ++i) {
        unsigned int random_label = distr_label(gen);
        vertices_and_labels[i] = make_pair(i, random_label);
        different_labels.insert(random_label);
    }

    unsigned int k = CustomRadixSort::sortByLabel(vertices_and_labels);
    
    // Check the number of labels
    BOOST_TEST(k == different_labels.size());
    // Check if the label value is correct (i.e 0 < l <= k)
    for(unsigned int i = 0; i < n; ++i) {
        BOOST_TEST(vertices_and_labels[i].second > 0);
        BOOST_TEST(vertices_and_labels[i].second <= k);
    }
}

BOOST_AUTO_TEST_SUITE_END()