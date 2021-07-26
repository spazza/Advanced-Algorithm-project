#include "Graph.hpp"

CustomGraph::Graph::Graph() : numEdges(0) {}

CustomGraph::Graph::Graph(const vector<unsigned int> &vertices) : numEdges(0) {
    for(auto vertex : vertices) 
        addVertex(vertex);
}

CustomGraph::Graph::Graph(const vector<unsigned int>  &vertices, const vector<unsigned int> &sources, const vector<unsigned int> &destinations) : Graph(vertices) {
    if(sources.size() == destinations.size())
        for(unsigned int i = 0; i < sources.size(); ++i)
            addEdge(sources[i], destinations[i]);            
}

void CustomGraph::Graph::addVertex(unsigned int vertex) {
    Vertex v(vertex);
    addVertex(v);
}

void CustomGraph::Graph::addVertex(const Vertex &vertex) {
    if(!isInside(vertex))
        vertices[vertex.value] = vertex;
}

void CustomGraph::Graph::addEdge(unsigned int src, unsigned int dst) {
    if(isInside(src) && isInside(dst) && src != dst)
        if(!vertices[src].isAdjacent(dst) && !vertices[dst].isAdjacent(src)) {
            vertices[src].addAdjacentVertex(dst);
            vertices[dst].addAdjacentVertex(src);
            numEdges++;
        }
}

void CustomGraph::Graph::addEdge(const Vertex &first, const Vertex &second) {
    addEdge(first.value, second.value);
}

unsigned int CustomGraph::Graph::size() {
    return vertices.size();
}

unsigned int CustomGraph::Graph::edgeSize() {
    return numEdges;
}

unordered_map<unsigned int, Vertex>& CustomGraph::Graph::getVertices() {
    return vertices;
}

bool CustomGraph::Graph::isInside(unsigned int vertex) {
    return vertices.find(vertex) != vertices.end();
}

bool CustomGraph::Graph::isInside(const Vertex &vertex) {
    return isInside(vertex.value);
}

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

void CustomGraph::Graph::connect() {
    for(unsigned int i = 0; i < size()-1; ++i)
        addEdge(i, i+1);
}

void CustomGraph::Graph::printGraph() {
    cout << "Graph adjacency list: " << endl;
    for(auto &vertex : vertices) 
        vertex.second.printAdjacentVertices();
}

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

void CustomGraph::Graph::fill_in(BijectionFunction bijFunction) {
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
vector<unsigned int> CustomGraph::Graph::lex_p() {
    vector<unsigned int> alphaInverse(vertices.size());
    unordered_set<unsigned int> ordered_vertices;
    vector<unsigned int> v_k = getVerticesKeys();
    unordered_set<unsigned int> v_t(v_k.begin(), v_k.end());
    Sets sets(v_t);

    for(unsigned int i = vertices.size()-1; i > 0; --i) {
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

    for(unsigned int i = vertices.size(); i > 0; ++i) {
        //pick an unnumbered vertex v with label(v) = k
        unsigned int v;
        for(auto it_v = vertices.begin(); it_v != vertices.begin(); ++it_v) {
            auto pos_it = find(unnumberedVertices.begin(), unnumberedVertices.end(), it_v->first);
            if((pos_it != unnumberedVertices.end()) && label[it_v->first] == k) {
                v = it_v->first;
                unnumberedVertices.erase(pos_it);
                break;
            }
        }

        alphaInverse[i] = v;

        unordered_map<unsigned int, list<unsigned int>> reach;
        for(unsigned int j = 1; j < k; ++j)
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
                reach[k].pop_front();

                for(auto it_z = vertices[w].getAdjVertices().begin(); it_z != vertices[w].getAdjVertices().end(); ++it_z) {
                    unsigned int z = *it_z;
                    reached.insert(z);
                    
                    if(label[z] < k) {
                        reach[label[z]].push_back(z);
                        label[z] = label[z] + 0.5;
                        g_alpha.push_back(pair<unsigned int, unsigned int>(v,z));
                    } else {
                        reach[k].push_back(z);
                    }
                }
            }
        }

        

        //sort unnumbered vertices by label(w) value

    }
    return g_alpha;
}

vector<unsigned int> sortByLabel(vector<unsigned int> unnemberded_vertices, unordered_map<unsigned int, float> label) {

}

vector<unsigned int> CustomGraph::Graph::getVerticesKeys() {
    vector<unsigned int> v_keys;
    for(auto it = vertices.begin(); it != vertices.end(); ++it)
        v_keys.push_back((*it).first);
    return v_keys;
}

void CustomGraph::Graph::clear() {
    vertices.clear();
    numEdges = 0;
}


void CustomGraph::Graph::generateRandomGraph(unsigned int num_vertices) {
    RandomGraphGenerator rg(num_vertices);
    rg.generate();

    clear();

    vector<unsigned int> rg_vertices = rg.getVertices();
    for(auto it = rg_vertices.begin(); it != rg_vertices.end(); ++it) 
        addVertex(*it);

    vector<unsigned int> rg_edges_src = rg.getEdgesSrc();
    vector<unsigned int> rg_edges_dst = rg.getEdgesDst();

    for(unsigned int i = 0; i < rg_edges_src.size(); ++i)
        addEdge(rg_edges_src[i], rg_edges_dst[i]);
}

/*
void CustomGraph::Graph::generateRandomGraph(unsigned int num_nodes) {
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
    
    uniform_int_distribution<> distr_nodes(0, num_nodes);
    while(edgeSize() < num_edges) {
        unsigned int src_vertex = distr_nodes(gen);
        unsigned int dst_vertex = distr_nodes(gen);
        addEdge(src_vertex, dst_vertex);
    }

    while(edgeSize() < num_edges)
        for(unsigned int i = 0; i < num_nodes; i++)
            for(unsigned int j = 1; j < num_nodes; j++)
            addEdge(i, j);
}*/



