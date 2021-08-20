#include <benchmark/benchmark.h>
#include "Graph.hpp"

// Performance evaluation of lex_m function.
// This version does not produce meaningful results because I can't control the number of edges.

static void BM_lex_m(benchmark::State& state) {
    CustomGraph::Graph g;   
    for(auto _ : state) {
        state.PauseTiming();
        g.generateRandomGraph(state.range(0));

        vector<unsigned int> graphVerticesVector(g.size());
        for(auto v : g.getVertices())
            graphVerticesVector.push_back(v.first);

        BijectionFunction bj (graphVerticesVector);

        unsigned int prev_edges = g.edgeSize();
        state.ResumeTiming();
        
        g.lex_m();
        state.SetComplexityN(g.size() * prev_edges);
    }
}

//BENCHMARK(BM_lex_m)->RangeMultiplier(2)->Range(2,512)->Complexity();
//BENCHMARK(BM_lex_m)->RangeMultiplier(2)->Range(2,1024)->Complexity(benchmark::oNSquared);

// Second version of lex_m evaluation
// Better results and control over the number of vertices and edges

static void BM_lex_m_2(benchmark::State& state) {
    CustomGraph::Graph g;   
    for(auto _ : state) {
        state.PauseTiming();
        g.generateRandomGraphPrecise(state.range(0));

        unsigned int prev_edges = g.edgeSize();
        state.ResumeTiming();
        
        g.lex_m();

        state.PauseTiming();
        state.SetComplexityN(g.size() * g.size());
        state.ResumeTiming();
    }
}

BENCHMARK(BM_lex_m_2)->RangeMultiplier(2)->Range(8,512)->Complexity();
BENCHMARK(BM_lex_m_2)->RangeMultiplier(2)->Range(8,512)->Complexity(benchmark::oNSquared);

BENCHMARK_MAIN();