#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

struct Vertex {
public:

    unsigned int value;

    Vertex() = default;

    Vertex(unsigned int value);

    void addAdjacentVertex(const Vertex& vertex);

    void addAdjacentVertex(unsigned int vertex);

    bool isAdjacent(const Vertex& vertex);

    bool isAdjacent(unsigned int vertex);

    void printAdjacentVertices();

    set<unsigned int>& getAdjVertices();

    bool operator==(const Vertex& other) {
        if(other.value == value && other.adjVertices == adjVertices)
            return true;
        else    
            return false;
    }

private:
    set<unsigned int> adjVertices;   
};

#endif