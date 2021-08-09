#ifndef BIJECTIONFUNCTION_H_
#define BIJECTIONFUNCTION_H_

#include <vector>
#include <unordered_map>

using namespace std;

/**
 * @brief Auxiliary structure that emulates the bijective function alpha. It is able to cope with its direct representation
 * and with its inverse.
 */
struct BijectionFunction {
public:
    /**
     * @brief Construct a new Bijection Function object that is empty.
     */
    BijectionFunction();

    /**
     * @brief Construct a new Bijection Function object that uses the input vertices as codomain of the bijection function.
     * @param vertices vector of vertices of a connected graph.
     */
    BijectionFunction(vector<unsigned int> &vertices);

    /**
     * @brief Get the vertex associated to the real number in input
     * @param index real number that corresponds to a vertex
     * @return unsigned int vertex
     */
    unsigned int alpha(unsigned int index);

    /**
     * @brief Get the real number associated to the vertex in input
     * @param vertex unsigned int that corresponds to a vertex of a graph
     * @return unsigned int real number associated to a vertex
     */
    unsigned int alphaInverse(unsigned int vertex);

private:
    /**
     * @brief structure that binds real numbers toward vertices
     */
    unordered_map<unsigned int, unsigned int> alpha_;

    /**
     * @brief structure that binds vertices toward real numbers
     */
    unordered_map<unsigned int, unsigned int> alphaInverse_;

};

#endif