#include "RandomGraphGenerator.hpp"

RandomGraphGenerator::RandomGraphGenerator(unsigned int num_vertices) : num_vertices(num_vertices) {}

vector<unsigned int> RandomGraphGenerator::getVertices() {
    return vertices;
}

vector<unsigned int> RandomGraphGenerator::getEdgesSrc() {
    return src_edges;
}

vector<unsigned int> RandomGraphGenerator::getEdgesDst() {
    return dst_edges;
}

void RandomGraphGenerator::generate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr_edge(num_vertices-1, (num_vertices*(num_vertices-1))/2);

    // num of edges in the graph between (n-1) and (n*(n-1) / 2)
    unsigned int num_edges = distr_edge(gen);

    boost::minstd_rand graph_gen;
    boost::graph_traits<Graph>::vertices_size_type n(num_vertices);
    boost::graph_traits<Graph>::edges_size_type m(num_edges);

    boost::adjacency_list<> g(ERGen(graph_gen, n, m, false), ERGen(), n);

    boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
 
    for(boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
        vertices.push_back((unsigned int) (*vi));

    boost::graph_traits<Graph>::edge_iterator ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei){
        src_edges.push_back((unsigned int) (*ei).m_source);
        dst_edges.push_back((unsigned int) (*ei).m_target);
    }
}


    
    
    

    