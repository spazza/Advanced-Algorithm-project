#include "BijectionFunction.hpp"

BijectionFunction::BijectionFunction(vector<unsigned int> vertices) {
    for(unsigned int i = 0; i < vertices.size(); ++i) {
        alpha_[i] = vertices[i];
        alphaInverse_[vertices[i]] = i;
    }
}

unsigned int BijectionFunction::alpha(unsigned int index) {
    return alpha_[index];;
}

unsigned int BijectionFunction::alphaInverse(unsigned int vertex) {
    return alphaInverse_[vertex];
}