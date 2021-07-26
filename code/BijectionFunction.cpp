#include "BijectionFunction.hpp"
/**
 * @brief Construct a new Bijection Function object that uses the input vertices as codomain of the bijection function.
 * @param vertices vector of vertices of a connected graph.
 */
BijectionFunction::BijectionFunction(vector<unsigned int> vertices) {
    for(unsigned int i = 0; i < vertices.size(); ++i) {
        alpha_[i] = vertices[i];
        alphaInverse_[vertices[i]] = i;
    }
}

/**
 * @brief Get the vertex associated to the real number in input
 * @param index real number that corresponds to a vertex
 * @return unsigned int vertex
 */
unsigned int BijectionFunction::alpha(unsigned int index) {
    return alpha_[index];;
}

/**
 * @brief Get the real number associated to the vertex in input
 * @param vertex unsigned int that corresponds to a vertex of a graph
 * @return unsigned int real number associated to a vertex
 */
unsigned int BijectionFunction::alphaInverse(unsigned int vertex) {
    return alphaInverse_[vertex];
}