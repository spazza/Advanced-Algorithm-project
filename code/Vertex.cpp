#include "Vertex.hpp"

Vertex::Vertex(unsigned int value) : value(value) {}

void Vertex::addAdjacentVertex(unsigned int vertex) {
    adjVertices.insert(vertex);
}

void Vertex::addAdjacentVertex(const Vertex &vertex) {
    addAdjacentVertex(vertex.value);
}

bool Vertex::isAdjacent(unsigned int vertex) {
    return find(adjVertices.begin(), adjVertices.end(), vertex) !=adjVertices.end();
}

bool Vertex::isAdjacent(const Vertex &vertex) {
    return isAdjacent(vertex.value);
}

void Vertex::printAdjacentVertices() {
    cout << "Vertex: " << value << endl;

    for(auto adjVertex : adjVertices)
        cout << " -> " << adjVertex;
    cout << endl;
}

set<unsigned int>& Vertex::getAdjVertices() {
    return adjVertices;
} 