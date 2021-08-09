#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.hpp"
#include "BijectionFunction.hpp"
#include "RandomGraphGenerator.hpp"
#include "Sets.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <random>

using namespace std;

namespace CustomGraph {

/**
 * @brief Main class of the project, it contains the three functions to be tested (fill_in, lex_p, lex_m) and all the functions
 * necessary to manage in a handy way a graph. An instance of this class will represent an undirected and connected graph, also auto-ring
 * are not allowed.
 */
struct Graph {
public:
    /**
     * @brief Construct a new empty Graph object.
     */
    Graph();

    /**
     * @brief Construct a new Graph object with verticies specified.
     * @param vertices vector of verticies that will compose the graph.
     */
    Graph(const vector<unsigned int> &vertices);

    /**
     * @brief Construct a new Graph object with verticies and edges specified.
     * @param vertices vector of verticies that will compose the graph.
     * @param sources vector of souces of the edges
     * @param destinations vector of destinations of the edges.
     */
    Graph(const vector<unsigned int> &vertices, const vector<unsigned int> &sources, const vector<unsigned int> &destinations); 
 
    /**
     * @brief Add a new vertex to the graph.
     * @param vertex value that represents the vertex.
     */
    void addVertex(unsigned int vertex);

    /**
     * @brief Add a new vertex to the graph.
     * @param vertex object that represents the vertex.
     */
    void addVertex(const Vertex &vertex);

    /**
     * @brief Add a new edge to the graph.
     * @param first source vertex of the edge.
     * @param second destination vertex of the edge.
     */
    void addEdge(unsigned int first, unsigned int second);

    /**
     * @brief Add a new edge to the graph.
     * @param first source vertex of the edge.
     * @param second destionation vertex of the edge.
     */
    void addEdge(const Vertex &first, const Vertex &second);

    /**
     * @brief Get the number of verticies in the graph.
     * @return unsigned int number of verticies.
     */
    unsigned int size();

    /**
     * @brief Get the number of edges in the graph.
     * @return unsigned int number of edges.
     */
    unsigned int edgeSize();

    /**
     * @brief Get the Vertices object that bind values of the vertices to the corresponding object.
     * @return unordered_map<unsigned int, Vertex>& data structure that stores the vertices. 
     */
    unordered_map<unsigned int, Vertex>& getVertices();

    /**
     * @brief Check if a vertex is inside the graph.
     * @param vertex number that represents the vertex.
     * @return true if the vertex is contained.
     * @return false if the vertex is not contained.
     */
    bool isInside(unsigned int vertex);

    /**
     * @brief Check if a vertex is inside the graph.
     * @param vertex object that represents the vertex.
     * @return true if the vertex is contained.
     * @return false if the vertex is not contained.
     */
    bool isInside(const Vertex &vertex);

    /**
     * @brief Check if the graph is connected.
     * @return true if it is connected.
     * @return false if it is not connected.
     */
    bool isConnected();

    /**
     * @brief In case there are some nodes in the graph that are not connected, connect them to the graph.
     */
    void connect();

    /**
     * @brief Print the adjacency list that is used to represent the graph.
     */
    void printGraph();

    /**
     * @brief Fill-in is a function that starting from a graph creates an elimination graph.
     * The v-elimination graph is obtained by adding edges such that all vertices adjacent to v are pairwise adjacent
     * and then v is deleted and also its incident edges. Applying recursively this process for all the vertices of an ordered graph it
     * will produce the so called fill-in of the graph.
     * The algorithm works in this way:
     * - For each i from 0 to n-1, n is the number of vertices in the graph, assing to v an ordering number.
     * - Then select k that is the vertex u with the minimum alpha-1 such that v is monotonely adjacent to u.
     * - Finally add fill-in edges, for each adjacent vertex w, if w is different from k then add w to the adjacent
     *   vertices of m(v) 
     * @param bijFunction object used to define a bijection function that associates each vertex to a natural number. It is used
     * to assign an ordering to the graph.
     */
    void fill_in(BijectionFunction &bijFunction);

    vector<unsigned int> lex_p();

    list<pair<unsigned int, unsigned int>> lex_m();

    void sortByLabel(vector<unsigned int> &unnumberded_vertices, unordered_map<unsigned int, float> &label,  unsigned int *k);

        /**
     * @brief Remove all the verticies and all the edges of the graph.
     */
    void clear();
    
    /**
     * @brief Utility function used to create a random graph from scatch. It explois the Erdos-Renyi model for creation of
     * random connected graphs.
     * @param num_vertices number of vertices that will compose the graph.
     */
    void generateRandomGraph(unsigned int num_vertices);

    void generateRandomGraphPrecise(unsigned int num_elements);

private:

    /**
     * @brief Auxiliary function that is used to perform a depth first search in the graph to check if it is connected. It is called
     * in the connect function and it is part of its logic.
     * @param v vertex to be searched.
     * @param visited_vertices vertices visited and not of the graph.
     */
    void DFS(unsigned int v, vector<pair<Vertex, bool>> &visited_vertices);

    /**
     * @brief Get the Vertices Keys object, extract them from the keys of the unordered map that represents the vertices.
     * @return vector<unsigned int> array representations of the vertices in the graph.
     */
    vector<unsigned int> getVerticesKeys();

    /**
     * @brief Structure that binds the value of the vertex with the corresponding vertex object.
     */
    unordered_map<unsigned int, Vertex> vertices;

    /**
     * @brief Number of edges in the graph.
     */
    unsigned int numEdges;
};

}

#endif