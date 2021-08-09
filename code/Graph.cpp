#include "Graph.hpp"

/**
 * @brief Construct a new empty Graph object.
 */
CustomGraph::Graph::Graph() : numEdges(0) {}

/**
 * @brief Construct a new Graph object with verticies specified.
 * @param vertices vector of verticies that will compose the graph.
 */
CustomGraph::Graph::Graph(const vector<unsigned int> &vertices) : numEdges(0) {
    for(auto vertex : vertices) 
        addVertex(vertex);
}

/**
 * @brief Construct a new Graph object with verticies and edges specified.
 * @param vertices vector of verticies that will compose the graph.
 * @param sources vector of souces of the edges
 * @param destinations vector of destinations of the edges.
 */
CustomGraph::Graph::Graph(const vector<unsigned int>  &vertices, const vector<unsigned int> &sources, const vector<unsigned int> &destinations) : Graph(vertices) {
    if(sources.size() == destinations.size())
        for(unsigned int i = 0; i < sources.size(); ++i)
            addEdge(sources[i], destinations[i]);            
}

/**
 * @brief Add a new vertex to the graph.
 * @param vertex value that represents the vertex.
 */
void CustomGraph::Graph::addVertex(unsigned int vertex) {
    Vertex v(vertex);
    addVertex(v);
}

/**
 * @brief Add a new vertex to the graph.
 * @param vertex object that represents the vertex.
 */
void CustomGraph::Graph::addVertex(const Vertex &vertex) {
    if(!isInside(vertex))
        vertices[vertex.value] = vertex;
}

/**
 * @brief Add a new edge to the graph.
 * @param first source vertex of the edge.
 * @param second destination vertex of the edge.
 */
void CustomGraph::Graph::addEdge(unsigned int src, unsigned int dst) {
    if(isInside(src) && isInside(dst) && src != dst)
        if(!vertices[src].isAdjacent(dst) && !vertices[dst].isAdjacent(src)) {
            vertices[src].addAdjacentVertex(dst);
            vertices[dst].addAdjacentVertex(src);
            numEdges++;
        }
}

/**
 * @brief Add a new edge to the graph.
 * @param first source vertex of the edge.
 * @param second destionation vertex of the edge.
 */
void CustomGraph::Graph::addEdge(const Vertex &first, const Vertex &second) {
    addEdge(first.value, second.value);
}

/**
 * @brief Get the number of verticies in the graph.
 * @return unsigned int number of verticies.
 */
unsigned int CustomGraph::Graph::size() {
    return vertices.size();
}

/**
 * @brief Get the number of edges in the graph.
 * @return unsigned int number of edges.
 */
unsigned int CustomGraph::Graph::edgeSize() {
    return numEdges;
}

/**
 * @brief Get the Vertices object that bind values of the vertices to the corresponding object.
 * @return unordered_map<unsigned int, Vertex>& data structure that stores the vertices. 
 */
unordered_map<unsigned int, Vertex>& CustomGraph::Graph::getVertices() {
    return vertices;
}

/**
 * @brief Check if a vertex is inside the graph.
 * @param vertex number that represents the vertex.
 * @return true if the vertex is contained.
 * @return false if the vertex is not contained.
 */
bool CustomGraph::Graph::isInside(unsigned int vertex) {
    return vertices.find(vertex) != vertices.end();
}

/**
 * @brief Check if a vertex is inside the graph.
 * @param vertex object that represents the vertex.
 * @return true if the vertex is contained.
 * @return false if the vertex is not contained.
 */
bool CustomGraph::Graph::isInside(const Vertex &vertex) {
    return isInside(vertex.value);
}

/**
 * @brief Check if the graph is connected.
 * @return true if it is connected.
 * @return false if it is not connected.
 */
bool CustomGraph::Graph::isConnected() {
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

/**
 * @brief In case there are some nodes in the graph that are not connected, connect them to the graph.
 */
void CustomGraph::Graph::connect() {
    for(unsigned int i = 0; i < size()-1; ++i)
        addEdge(i, i+1);
}

/**
 * @brief Print the adjacency list that is used to represent the graph.
 */
void CustomGraph::Graph::printGraph() {
    cout << "Graph adjacency list: " << endl;
    for(auto &vertex : vertices) 
        vertex.second.printAdjacentVertices();
}

/**
 * @brief Auxiliary function that is used to perform a depth first search in the graph to check if it is connected. It is called
 * in the connect function and it is part of its logic.
 * @param v vertex to be searched.
 * @param visited_vertices vertices visited and not of the graph.
 */
void CustomGraph::Graph::DFS(unsigned int v, vector<pair<Vertex, bool>> &visited_vertices) {
    visited_vertices[v].second = true;

    Vertex &vertex = visited_vertices[v].first;
    for(auto it = vertex.getAdjVertices().begin(); it != vertex.getAdjVertices().end(); ++it) {
        
        for(unsigned int i = 0; i < visited_vertices.size(); ++i)
            if(visited_vertices[i].first.value == (*it))
                if(visited_vertices[i].second == false)
                    DFS(i, visited_vertices);
    }
}

/**
 * @brief Fill-in is a function that starting from a graph creates an elimination graph.
 * The v-elimination graph is obtained by adding edges such that all vertices adjacent to v are pairwise adjacent
 * and then v is deleted and also its incident edges. Applying recursively this process for all the vertices of an ordered graph it
 * will produce the so called fill-in of the graph.
 * The algorithm works in this way:
 * - For each i from 0 to n-1, n is the number of vertices in the graph, select a vertex v = alpha(i).
 * - Then select k that is the vertex u with the minimum alpha-1 such that v is monotonely adjacent to u.
 * - Finally add fill-in edges, for each adjacent vertex w, if w is different from k then add w to the adjacent
 *   vertices of m(v) 
 * @param bijFunction object used to define a bijection function that associates each vertex to a natural number. It is used
 * to assign an ordering to the graph.
 */
void CustomGraph::Graph::fill_in(BijectionFunction &bijFunction) {
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

/**
 * @brief 
 * 
 * @return vector<unsigned int> 
 */
vector<unsigned int> CustomGraph::Graph::lex_p() {
    vector<unsigned int> alphaInverse(vertices.size());
    unordered_set<unsigned int> ordered_vertices;
    vector<unsigned int> v_k = getVerticesKeys();
    unordered_set<unsigned int> v_t(v_k.begin(), v_k.end());
    Sets sets(v_t);

    for(int i = vertices.size()-1; i >= 0; --i) {
        sets.clearEmptyCells();
        
        // pick next vertex to number
        unsigned int v = sets.get();

        // delete cell of vertex from set
        sets.removeDefinitely(v);

        // assign v to the number i
        alphaInverse[i] = v;
        ordered_vertices.insert(v);

        unordered_set<Cell*> fixlist;

        // for each w adjacent to v
        for(auto it_w = vertices[v].getAdjVertices().begin(); it_w != vertices[v].getAdjVertices().end(); ++it_w) {
            unsigned int w = *it_w;
            // that has not been selected yet
            if(ordered_vertices.find(w) == ordered_vertices.end()) {
                //delete cell of w from set
                sets.remove(w);

                Cell *prev_cell = sets.getVertexPosition(w);
                auto h = fixlist.find(prev_cell); // other cell
                // if h is an old set then create a new set
                if(h == fixlist.end()) {
                    sets.addSet(prev_cell, w);
                } else {
                    sets.addCell(prev_cell->next, w);
                }
                fixlist.insert(prev_cell);
            }
        }
        fixlist.clear();
    }
    return alphaInverse;
}

list<pair<unsigned int, unsigned int>> CustomGraph::Graph::lex_m() {
    list<pair<unsigned int, unsigned int>> g_alpha;
    unordered_map<unsigned int, float> label;
    unordered_set<unsigned int> reached;
    vector<unsigned int> unnumberedVertices;
    vector<unsigned int> alphaInverse(vertices.size());

    for(auto it_v = vertices.begin(); it_v != vertices.end(); ++it_v) {
        label[it_v->first] = 1;
        unnumberedVertices.push_back(it_v->first);
    }
        
    unsigned int k = 1;

    unordered_map<unsigned int, list<unsigned int>> reach;
    for(int i = vertices.size(); i > 0; --i) {
        //pick an unnumbered vertex v with label(v) = k
        unsigned int v;
        for(auto it_v = vertices.begin(); it_v != vertices.end(); ++it_v) {
            auto pos_it = find(unnumberedVertices.begin(), unnumberedVertices.end(), it_v->first);
            if((pos_it != unnumberedVertices.end()) && label[it_v->first] == k) {
                v = it_v->first;
                unnumberedVertices.erase(pos_it);
                break;
            }
        }

        //maybe useless
        alphaInverse[i-1] = v;

        reach.clear();
        for(unsigned int j = 1; j <= k; ++j)
            reach[j] = list<unsigned int>();

        //mark all unnumbered vertices unreached
        for(auto it_w = vertices[v].getAdjVertices().begin(); it_w != vertices[v].getAdjVertices().end(); ++it_w) {
            unsigned int w = *it_w;

            if(find(unnumberedVertices.begin(), unnumberedVertices.end(), w) != unnumberedVertices.end()) {
                reach[label[w]].push_back(w);
                reached.insert(w);  
                label[w] = label[w] + 0.5;
                g_alpha.push_back(pair<unsigned int, unsigned int>(v,w));
            }
        }

        for(unsigned int j = 1; j <= k; ++j) {
            while(reach[j].size() != 0) {
                // delete a vertex w from reach(j)
                unsigned int w = reach[j].front();
                reach[j].pop_front();

                for(auto it_z = vertices[w].getAdjVertices().begin(); it_z != vertices[w].getAdjVertices().end(); ++it_z) {
                    unsigned int z = *it_z;
                    if(reached.find(z) == reached.end()) {
                        reached.insert(z);
                        
                        if(label[z] > j) {
                            reach[label[z]].push_back(z);
                            label[z] = label[z] + 0.5;
                            g_alpha.push_back(pair<unsigned int, unsigned int>(v,z));
                        } else
                            reach[j].push_back(z);
                        
                    }
                }
            }
        }
        //sort unnumbered vertices by label(w) value
        sortByLabel(unnumberedVertices, label, &k);
    }
    return g_alpha;
}

void CustomGraph::Graph::sortByLabel(vector<unsigned int> &unnumberded_vertices, unordered_map<unsigned int, float> &label, unsigned int *k) {
    unordered_set<float> different_k;

    for(unsigned int i = 0; i < unnumberded_vertices.size(); ++i) {
        for(unsigned int j = 0; j < unnumberded_vertices.size(); ++j) 
            if((label.find(unnumberded_vertices[i]) != label.end()) && (label.find(unnumberded_vertices[j]) != label.end())) 
                if(label[unnumberded_vertices[i]] > label[unnumberded_vertices[j]]) {
                    unsigned int temp = unnumberded_vertices[i];
                    unnumberded_vertices[i] = unnumberded_vertices[j];
                    unnumberded_vertices[j] = temp;
                }
    }

    for(unsigned int i = 0; i < unnumberded_vertices.size(); ++i) 
        if(different_k.find(label[unnumberded_vertices[i]]) == different_k.end()) 
            different_k.insert(label[unnumberded_vertices[i]]);

    unsigned int new_k = different_k.size();

    float prev_k = label[unnumberded_vertices[0]] + 1;
    for(unsigned int i = 0; i < unnumberded_vertices.size(); ++i) {
        if(label[unnumberded_vertices[i]] != prev_k) {
            prev_k = label[unnumberded_vertices[i]];
            label[unnumberded_vertices[i]] = new_k;
            new_k--;
        } else {
            label[unnumberded_vertices[i]] = label[unnumberded_vertices[i-1]];
        }
    }

    *k = different_k.size();
}

/**
 * @brief Get the Vertices Keys object, extract them from the keys of the unordered map that represents the vertices.
 * @return vector<unsigned int> array representations of the vertices in the graph.
 */
vector<unsigned int> CustomGraph::Graph::getVerticesKeys() {
    vector<unsigned int> v_keys;
    for(auto it = vertices.begin(); it != vertices.end(); ++it)
        v_keys.push_back((*it).first);
    return v_keys;
}

/**
 * @brief Remove all the verticies and all the edges of the graph.
 */
void CustomGraph::Graph::clear() {
    vertices.clear();
    numEdges = 0;
}

/**
 * @brief Utility function used to create a random graph from scatch. It explois the Erdos-Renyi model for creation of
 * random connected graphs.
 * @param num_vertices number of vertices that will compose the graph.
 */
void CustomGraph::Graph::generateRandomGraph(unsigned int num_vertices) {
    RandomGraphGenerator rg(num_vertices);
    rg.generate();

    vector<unsigned int> rg_vertices = rg.getVertices();
    for(auto it = rg_vertices.begin(); it != rg_vertices.end(); ++it) 
        addVertex(*it);

    vector<unsigned int> rg_edges_src = rg.getEdgesSrc();
    vector<unsigned int> rg_edges_dst = rg.getEdgesDst();

    for(unsigned int i = 0; i < rg_edges_src.size(); ++i)
        addEdge(rg_edges_src[i], rg_edges_dst[i]);
}

void CustomGraph::Graph::generateRandomGraphPrecise(unsigned int num_elements) {
    typedef boost::adjacency_list<> Graph;
    typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;

    random_device rd;
    mt19937 gen(rd());

    unsigned int num_vertices = 1;
    
    while(num_vertices + ((num_vertices * (num_vertices - 1)) / 2) < num_elements) {
        uniform_int_distribution<> distr_vertices(num_vertices, num_elements / 2);
        num_vertices = distr_vertices(gen);
    }
    
    unsigned int num_edges = num_elements - num_vertices;

    boost::minstd_rand graph_gen;
    boost::graph_traits<Graph>::vertices_size_type n(num_vertices);
    boost::graph_traits<Graph>::edges_size_type m(num_edges);

    boost::adjacency_list<> g(ERGen(graph_gen, n, m, false), ERGen(), n);

    boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
    for(boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
        addVertex((unsigned int) *vi);

    boost::graph_traits<Graph>::edge_iterator ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei)
        addEdge((unsigned int) (*ei).m_source, (unsigned int) (*ei).m_target);
    
}