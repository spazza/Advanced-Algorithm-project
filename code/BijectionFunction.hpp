#ifndef BIJECTIONFUNCTION_H_
#define BIJECTIONFUNCTION_H_

#include <unordered_map>
#include <vector>

using namespace std;

struct BijectionFunction {
public:
    BijectionFunction(vector<unsigned int> vertices);

    unsigned int alpha(unsigned int index);

    unsigned int alphaInverse(unsigned int vertex);

private:
    unordered_map<unsigned int, unsigned int> alpha_;

    unordered_map<unsigned int, unsigned int> alphaInverse_;

};

#endif