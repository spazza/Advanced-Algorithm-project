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

    DFS(0, visited_vertices);

    for(unsigned int i = 0; i < visited_vertices.size(); ++i) 
        if(!visited_vertices[i].second)
            return false;    
    return true;
}

/**
 * @brief In case there are some nodes in the graph that are not connected, connect all consecutive nodes.
 * To be used only in emergencyin the uncommon case when the random graph generation produces a non-connected graph.
 */
void CustomGraph::Graph::connect() {
    for(unsigned int i = 0; i < size()-1; ++i)
        addEdge(i, i+1);
}

/**
 * @brief Remove all the verticies and all the edges of the graph.
 */
void CustomGraph::Graph::clear() {
    vertices.clear();
    numEdges = 0;
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
 * Being v a vertex of the graph, the v-elimination graph is obtained by adding edges such that all vertices adjacent to v are pairwise 
 * adjacent. Applying recursively this process for all the vertices of an ordered graph it will produce the so called fill-in of the graph.
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
 * @brief Lex_p is a function that tries to find a perfect ordering inside a graph.
 * Alpha is a perfect ordering if it's not necessary to add any other edge to eliminate the graph.
 * The algorithm exploits a sort of breadth-first search, when a vertex is visited it passes to the successive
 * order and a label is assigned to it.
 * An ordering is produced in any case, even if it is not perfetct. In that case it's suggested to check it using the
 * function fill-in.
 * The algorithm works in this way:
 * - All the vertices are inserted into sets(0)
 * - For each i = n-1 until 0 
 * -   Select a vertex v inside the set with highest index
 * -   Delete the cell that contains v from the set
 * -   Assign v to the order i
 * -   For each vertex w adjacent to v that has not been ordered yet.
 * -      Delete the cell of w from its set
 * -      Move w in the set with the successive order, checking if it already existent
 * -      Update the position of w
 * @return vector<unsigned int> structure that contains the ordered vertices of the perfect ordering procedure.
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

/**
 * @brief Lex_m is a function that finds a minimal ordering inside a graph.
 * Alpha is a minimal ordering if adding some edges I can eliminate the graph.
 * The algorithm exploits a sort of breadth-first search and during the search each unnumbered vertex has an associated label
 * that is updated at each visit based on the depth.
 * The ordering produced is surely minimal, but it may not be minimum.
 * The algorithm works in this way:
 * - A label with value 1 is assigned to all vertices.
 * - For each i = n-1 until 0 
 * -    Select a vertex v with the highest label
 * -    Assign v to the order i
 * -    For each w adjacent to v
 * -        Add it to the reached vertices at level l(w), mark w as reached, update its label
 * -    For each label level j
 * -        Delete a vertex w from the reached of label j
 * -        For each z adjacent to w
 * -            If label(z) is less than j
 * -                Add z to the reached vertices at level l(z), update its label, add edge {v,z} to the graph
 * -            Else
 * -                Add z to the reached vertices at level j
 * -    Sort unnumbered vertices by label value and redefine k appropriately               
 * @return vector<unsigned int> structure that contains the ordered vertices of the minimal ordering procedure.
 */
vector<unsigned int> CustomGraph::Graph::lex_m() {
    vector<unsigned int> alphaInverse(vertices.size());
    vector<pair<unsigned int, float>> vertices_and_label(vertices.size());

    int i = 0;
    for(auto v = vertices.begin(); v != vertices.end(); ++v, ++i) 
        vertices_and_label[i] = make_pair(v->first, 1);

    unsigned int k = 1;

    for(int i = vertices.size(); i > 0; --i) {
        //pick an unnumbered vertex v with label(v) = k
        unsigned int v = vertices_and_label[0].first;

        // delete the element that now is numbered
        vertices_and_label.erase(vertices_and_label.begin());

        // assign v the number i
        alphaInverse[i-1] = v;

        unordered_map<unsigned int, list<unsigned int>> reach;
        unordered_set<unsigned int> reached;
        reached.insert(alphaInverse.begin(), alphaInverse.end());

        // Initialize the lists for each level j up to k
        for(unsigned int j = 1; j <= k; ++j)
            reach[j] = list<unsigned int>();

        //mark all unnumbered vertices unreached
        for(auto it_w = vertices[v].getAdjVertices().begin(); it_w != vertices[v].getAdjVertices().end(); ++it_w) {
            unsigned int w = *it_w;

            auto it = find_if(vertices_and_label.begin(), vertices_and_label.end(), [w](pair<unsigned int, float> &p) {
                return p.first == w;
            });

            if(it != vertices_and_label.end()) {
                reach[it->second].push_back(w);
                reached.insert(w);  
                it->second +=  0.5;
                addEdge(v,w);
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

                        auto it = find_if(vertices_and_label.begin(), vertices_and_label.end(), [z](pair<unsigned int, float> &p) {
                            return p.first == z;
                        });
                        
                        if(it->second > j) {
                            reach[it->second].push_back(z);
                            it->second += 0.5;
                            addEdge(v,z);
                        } else
                            reach[j].push_back(z);
                    }
                }
            }
        }

        //sort unnumbered vertices by label(w) value
        if(vertices_and_label.size() != 0)
            k = CustomRadixSort::sortByLabel(vertices_and_label);
    }
    return alphaInverse;
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
 * @brief Utility function used to create a random graph from scratch. It exploits the Erdos-Renyi model for creation of
 * random connected graphs, the only parameter specified is the number of vertices, the function will generate edges randomly.
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

    if(!isConnected())
        connect();
}

/**
 * @brief Utility function used to create a random graph from scratch. It exploits the Erdos-Renyi model for creation of
 * random connected graphs, the input parameter indicates the sum between the number of vertices and the number of edges.
 * The function will then produce a graph which sum between number of vertices and number of edges is equal to num_elements.
 * @param num_elements number of elements in the graph, it is given by the sum of the number of vertices and the number of edges.
 */
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
    
    if(!isConnected())
        connect();
}