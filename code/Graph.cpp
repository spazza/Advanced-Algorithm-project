#include "Graph.hpp"

Graph::Graph() : numEdges(0) {}

Graph::Graph(const vector<unsigned int> &vertices) : numEdges(0) {
    for(auto vertex : vertices) 
        addVertex(vertex);
}

Graph::Graph(const vector<unsigned int>  &vertices, const vector<unsigned int> &sources, const vector<unsigned int> &destinations) : Graph(vertices) {
    if(sources.size() == destinations.size())
        for(unsigned int i = 0; i < sources.size(); ++i)
            addEdge(sources[i], destinations[i]);            
}

void Graph::addVertex(unsigned int vertex) {
    Vertex v(vertex);
    addVertex(v);
}

void Graph::addVertex(const Vertex &vertex) {
    if(!isInside(vertex))
        vertices[vertex.value] = vertex;
}

void Graph::addEdge(unsigned int src, unsigned int dst) {
    if(isInside(src) && isInside(dst) && src != dst)
        if(!vertices[src].isAdjacent(dst) && !vertices[dst].isAdjacent(src)) {
            vertices[src].addAdjacentVertex(dst);
            vertices[dst].addAdjacentVertex(src);
            numEdges++;
        }
}

void Graph::addEdge(const Vertex &first, const Vertex &second) {
    addEdge(first.value, second.value);
}

unsigned int Graph::size() {
    return vertices.size();
}

unsigned int Graph::edgeSize() {
    return numEdges;
}

unordered_map<unsigned int, Vertex>& Graph::getVertices() {
    return vertices;
}

bool Graph::isInside(unsigned int vertex) {
    return vertices.find(vertex) != vertices.end();
}

bool Graph::isInside(const Vertex &vertex) {
    return isInside(vertex.value);
}

bool Graph::isConnected() {
    vector<pair<Vertex, bool>> visited_vertices(vertices.size());

    int i = 0;
    for(auto it = vertices.begin(); it != vertices.end(); ++it, ++i) {
        pair<Vertex, bool> temp_pair((*it).second, false);
        visited_vertices[i] = temp_pair;
    }
    /*
    for(unsigned int i = 0; i < vertices.size(); ++i) {
        pair<Vertex, bool> temp_pair(vertices[i], false);
        visited_vertices[i] = temp_pair;
    }*/

    DFS(0, visited_vertices);

    for(unsigned int i = 0; i < visited_vertices.size(); ++i) 
        if(!visited_vertices[i].second)
            return false;    
    return true;
}

void Graph::printGraph() {
    cout << "Graph adjacency list: " << endl;
    for(auto &vertex : vertices) 
        vertex.second.printAdjacentVertices();
}

void Graph::DFS(unsigned int v, vector<pair<Vertex, bool>> &visited_vertices) {
    visited_vertices[v].second = true;

    Vertex &vertex = visited_vertices[v].first;
    for(auto it = vertex.getAdjVertices().begin(); it != vertex.getAdjVertices().end(); ++it) {
        
        for(unsigned int i = 0; i < visited_vertices.size(); ++i)
            if(visited_vertices[i].first.value == (*it))
                if(visited_vertices[i].second == false)
                    DFS(i, visited_vertices);
    }
}

void Graph::fill_in(BijectionFunction bijFunction) {
    unsigned int n = vertices.size();

    for(unsigned int i = 0; i < n-1; ++i) {
        unsigned int k = n-1;
        unsigned int v = bijFunction.alpha(i);

        for(auto w : vertices[v].getAdjVertices()) 
            if(bijFunction.alphaInverse(v) < bijFunction.alphaInverse(w))
                k = min(k, bijFunction.alphaInverse(w));
        
        unsigned int m = k;

        for(auto w : vertices[v].getAdjVertices()) 
            if(bijFunction.alphaInverse(w) > m)
                addEdge(bijFunction.alpha(m), w);
    }
    
}

void Graph::generateRandomGraph(unsigned int num_nodes) {
    clear();
    srand(time(NULL));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr_edge(num_nodes-1, (num_nodes*(num_nodes-1))/2);
    // num of edges in the graph between (n-1) and (n*(n-1) / 2)
    unsigned int num_edges = distr_edge(gen);

    for(unsigned int i = 0; i < num_nodes; ++i)
        addVertex(i);

    for(unsigned int i = 0; i < num_nodes-1; ++i)
        addEdge(i, i+1);
        
    /*
    uniform_int_distribution<> distr_nodes(0, num_nodes);
    while(edgeSize() < num_edges) {
        unsigned int src_vertex = distr_nodes(gen);
        unsigned int dst_vertex = distr_nodes(gen);
        addEdge(src_vertex, dst_vertex);
    }*/

    while(edgeSize() < numEdges)
        for(unsigned int i = 0; i < num_nodes; i++)
            for(unsigned int j = 1; j < num_nodes; j++)
            addEdge(i, j);

}

void Graph::clear() {
    vertices.clear();
    numEdges = 0;
}



