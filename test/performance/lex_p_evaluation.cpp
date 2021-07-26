#include <benchmark/benchmark.h>
#include "Graph.hpp"

static void BM_lex_p(benchmark::State& state) {
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
        
        g.lex_p();
        state.SetComplexityN(g.size() + prev_edges);
    }
}

BENCHMARK(BM_lex_p)->RangeMultiplier(2)->Range(2,2048)->Complexity();
BENCHMARK(BM_lex_p)->RangeMultiplier(2)->Range(2,2048)->Complexity(benchmark::oN);

BENCHMARK_MAIN();