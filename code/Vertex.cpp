#include "Vertex.hpp"

/**
 * @brief Construct a new Vertex object with an integer value.
 * @param value integer that represents the vertex.
 */
Vertex::Vertex(unsigned int value) : value(value) {}

/**
 * @brief Add an adjacent vertex to the current one. 
 * @param vertex adjacent vertex.
 */
void Vertex::addAdjacentVertex(unsigned int vertex) {
    adjVertices.insert(vertex);
}
/**
 * @brief Add an adjacent vertex to the current one.
 * @param vertex adjacent vertex.
 */
void Vertex::addAdjacentVertex(const Vertex &vertex) {
    addAdjacentVertex(vertex.value);
}

/**
 * @brief Check if the input vertex is adjacent to the current one.
 * @param vertex which adjacency must be check.
 * @return true if the input vertex is adjacent.
 * @return false if the input vertex is no adjacent.
 */  
bool Vertex::isAdjacent(unsigned int vertex) {
    return find(adjVertices.begin(), adjVertices.end(), vertex) !=adjVertices.end();
}

/**
 * @brief Check if the input vertex is adjacent to the current one.
 * @param vertex which adjacency must be check.
 * @return true if the input vertex is adjacent.
 * @return false if the input vertex is no adjacent.
 */
bool Vertex::isAdjacent(const Vertex &vertex) {
    return isAdjacent(vertex.value);
}

/**
 * @brief print a list of the adjacent vertices to the current vertex.
 */
void Vertex::printAdjacentVertices() {
    cout << "Vertex: " << value << endl;

    for(auto adjVertex : adjVertices)
        cout << " -> " << adjVertex;
    cout << endl;
}

/**
 * @brief Get the list of the adjacent vertices.
 * @return set<unsigned int>& vertices adjacent to the current one.
 */
unordered_set<unsigned int>& Vertex::getAdjVertices() {
    return adjVertices;
} 