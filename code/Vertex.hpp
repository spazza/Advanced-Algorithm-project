#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;

/**
 * @brief Auxiliary structure to manage a vertex of a graph and its adjacent vertices.
 */
struct Vertex {
public:
    /**
     * @brief value of the vertex.
     */
    unsigned int value;

    /**
     * @brief Construct a new Vertex object.
     */
    Vertex() = default;

    /**
     * @brief Construct a new Vertex object with an integer value.
     * @param value integer that represents the vertex.
     */
    Vertex(unsigned int value);

    /**
     * @brief Add an adjacent vertex to the current one. 
     * @param vertex adjacent vertex.
     */
    void addAdjacentVertex(unsigned int vertex);

    /**
     * @brief Add an adjacent vertex to the current one.
     * @param vertex adjacent vertex.
     */
    void addAdjacentVertex(const Vertex& vertex);

    /**
     * @brief check if the input vertex is adjacent to the current one.
     * @param vertex which adjacency must be check.
     * @return true if the input vertex is adjacent.
     * @return false if the input vertex is no adjacent.
     */    
    bool isAdjacent(unsigned int vertex);
    
    /**
     * @brief check if the input vertex is adjacent to the current one.
     * @param vertex which adjacency must be check.
     * @return true if the input vertex is adjacent.
     * @return false if the input vertex is no adjacent.
     */
    bool isAdjacent(const Vertex& vertex);

    /**
     * @brief print a list of the adjacent vertices to the current vertex.
     */
    void printAdjacentVertices();

    /**
     * @brief Get the list of the adjacent vertices.
     * @return set<unsigned int>& vertices adjacent to the current one.
     */
    unordered_set<unsigned int>& getAdjVertices();

    /**
     * @brief Compare two vertices, they are equal if they have the same value and the
     * same adjacent vertices.
     * @param other vertex to be compared with the current one.
     * @return true if the two vertices are equal.
     * @return false  if thw two vertices are different.
     */
    bool operator==(const Vertex& other) {
        if(other.value == value && other.adjVertices == adjVertices)
            return true;
        else    
            return false;
    }

private:
    /**
     * @brief set of vertices adjacent to the current one.
     */
    unordered_set<unsigned int> adjVertices;   
};

#endif