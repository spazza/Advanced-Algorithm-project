#include <benchmark/benchmark.h>
#include "Graph.hpp"

// Performance evaluation of fill-in function
// Results of this version are coherent with the expected ones, however I can control 
// only the number of vertices and not the number of edges.

static void BM_lex_p(benchmark::State& state) {
    CustomGraph::Graph g;   
    for(auto _ : state) {
        state.PauseTiming();
        g.generateRandomGraph(state.range(0));

        unsigned int prev_edges = g.edgeSize();
        state.ResumeTiming();
        
        g.lex_p();
        state.SetComplexityN(g.size() + prev_edges);
    }
}

//BENCHMARK(BM_lex_p)->RangeMultiplier(2)->Range(2,2048)->Complexity();
//BENCHMARK(BM_lex_p)->RangeMultiplier(2)->Range(2,2048)->Complexity(benchmark::oN);

// Second version lex_p evaluation
// Better results and control over the number of vertices and edges

static void BM_lex_p_2(benchmark::State& state) {
    CustomGraph::Graph g;
    for(auto _ : state) {
        // Graph creation discarded from the evaluation
        state.PauseTiming();
        g.clear();
        g.generateRandomGraphPrecise(state.range(0));
        state.ResumeTiming();

        g.lex_p();
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_lex_p_2)->RangeMultiplier(2)->Range(8,2<<12)->Complexity();
BENCHMARK(BM_lex_p_2)->RangeMultiplier(2)->Range(8,2<<12)->Complexity(benchmark::oN);

BENCHMARK_MAIN();