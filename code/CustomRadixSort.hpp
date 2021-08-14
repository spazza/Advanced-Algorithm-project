#ifndef CUSTOMRADIXSORT_H_
#define CUSTOMRADIXSORT_H_

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

/**
 * @brief Auxiliary structure that allows to reorder a vector according to its label values. It also reassigns to 
 * the vector label values that are integers. A custom version of radix-sort is used to sort the vector.
 */
struct CustomRadixSort {
public:

    /**
     * @brief Function that reassigns to the vector an integer number of label values and that sorts the vector
     * according to the value of the labels. It implements a custom version of radix-sort.
     * @param vertices_and_labels vector to be ordered.
     * @return unsigned int new number of labels in the vector.
     */
    unsigned int static sortByLabel(vector<pair<unsigned int, float>> &vertices_and_labels) {
        // count the number of different labels
        unordered_set<float> different_k;
        for(unsigned int i = 0; i < vertices_and_labels.size(); ++i) 
            if(different_k.find(vertices_and_labels[i].second) == different_k.end()) 
                different_k.insert(vertices_and_labels[i].second);

        // sort the distinct labels
        vector<float> distinct_labels(different_k.begin(), different_k.end());
        sort(distinct_labels.rbegin(), distinct_labels.rend());

        // create a structure that binds old labels with new labels
        vector<pair<float, unsigned int>> label_binding(different_k.size());

        label_binding[0] = make_pair(distinct_labels[0], different_k.size());
        for(unsigned int i = 1; i < distinct_labels.size(); ++i) 
            label_binding[i] = make_pair(distinct_labels[i], label_binding[i-1].second - 1);
        
        // assign new labels 
        for(auto &el : vertices_and_labels)
            for(auto &lb : label_binding)
                if(el.second == lb.first)
                    el.second = lb.second;

        //sort the vector using radix-sort
        unsigned int max = getMaxLabel(vertices_and_labels);

        for(int exp = 1; max / exp > 0; exp *= 10)
            counting_sort(vertices_and_labels, exp);

        // revert the vector because it is in ascending order
        reverse(vertices_and_labels.begin(), vertices_and_labels.end());

        return different_k.size();
    }

private:    

    /**
     * @brief Utility function to get the maximum label inside the vector.
     * @param vertices_and_labels vector to be analyzed
     * @return unsigned int maximum label inside the vector.
     */
    unsigned int static getMaxLabel(vector<pair<unsigned int, float>> &vertices_and_labels) {
        unsigned int max = 0;

        for(auto &e: vertices_and_labels)
            if(e.second > max)
                max = e.second;

        return max;
    }

    /**
     * @brief Function that performs counting-sort of the vector according to the digit represented by exp.
     * @param vertices_and_labels vector to be sorted.
     * @param exp value that represents 10^i, where i is the current digit number.
     */
    void static counting_sort(vector<pair<unsigned int, float>> &vertices_and_labels, int exp) {
        vector<pair<unsigned int, float>> output(vertices_and_labels.size());
        unsigned int count[10] = {0};

        for(unsigned int i = 0; i < vertices_and_labels.size(); ++i) {
            unsigned int l = vertices_and_labels[i].second; 
            count[(l / exp) % 10]++;
        }
        
        for(int i = 1; i < 10; ++i)
            count[i] += count[i-1];

        for(int i = vertices_and_labels.size()-1; i >= 0; --i) {
            unsigned int l = vertices_and_labels[i].second;
            output[count[(l / exp) % 10] - 1] = vertices_and_labels[i];
            count[(l / exp) % 10]--;
        }   

        for(unsigned int i = 0; i < vertices_and_labels.size(); ++i)
            vertices_and_labels[i] = output[i];
    }
};

#endif