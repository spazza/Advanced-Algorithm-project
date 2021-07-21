#include "Graph.hpp"

Vertex::Vertex(unsigned int value) : value(value), adjVertices()  {}

void Vertex::addAdjacentVertex(unsigned int vertex) {
    adjVertices.push_back(vertex);
}

bool Vertex::isAdjacent(unsigned int dest) {
    return find(adjVertices.begin(), adjVertices.end(), dest) !=adjVertices.end();
}

void Vertex::printAdjacentVertices() {
    cout << "Vertex: " << value << endl;

    for(auto adjVertex : adjVertices)
        cout << " -> " << adjVertex;
    cout << endl;
}

Graph::Graph(list<unsigned int> const &vertices) {
    this->vertices.resize(vertices.size());
    for(auto value : vertices) {
        Vertex v(value);
        this->vertices.push_back(v);
    }
}

Graph::Graph(list<unsigned int> const &vertices, vector<unsigned int> const &sources, vector<unsigned int> const &destinations) : Graph(vertices) {
    if(sources.size() == destinations.size())
        for(unsigned int i = 0; i < sources.size(); ++i)
            addEdge(sources[i], destinations[i]);            
}

void Graph::addVertex(unsigned int vertex) {
    Vertex v(vertex);
    vertices.push_back(v);
}

void Graph::addEdge(unsigned int src, unsigned int dst) {
    if(isInTheGraph(src) && isInTheGraph(dst))
        for(auto &vertex : vertices)
            if(vertex.value == src)
                vertex.addAdjacentVertex(dst);
}

unsigned int Graph::size() {
    return vertices.size();
}

list<Vertex>& Graph::getVertices() {
    return vertices;
}

bool Graph::isInTheGraph(unsigned int vertex) {
    for(auto &v : vertices)
        if(v.value == vertex)
            return true;
    return false;
}

void Graph::printVertices() {
    cout << "Graph vertices: " << endl;
    for(auto &vertex : vertices)
        cout << vertex.value << " , ";
    cout << endl;
}

void Graph::printGraph() {
    cout << "Graph adjacency list: " << endl;
    for(auto &vertex : vertices) 
        vertex.printAdjacentVertices();
}

/*
void Graph::fill_in() {
    unsigned int n = adjList.size();
    vector<bool> test;
    test.resize(n);

    for(unsigned int j = 0; j < n; ++j)
        test[j] = false;
    
    for(unsigned int i = 0; i < n-1; ++i) {
        unsigned int k = n;
        unsigned int v = i;

        for(auto )
    } 
}*/