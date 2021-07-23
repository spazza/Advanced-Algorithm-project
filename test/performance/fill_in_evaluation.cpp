#include <benchmark/benchmark.h>
#include "Graph.hpp"

static void BM_fill_in(benchmark::State& state) {
    Graph g;   
    for(auto _ : state) {
        state.PauseTiming();
        g.generateRandomGraph(state.range(0));

        vector<unsigned int> graphVerticesVector(g.size());
        for(auto v : g.getVertices())
            graphVerticesVector.push_back(v.first);

        BijectionFunction bj (graphVerticesVector);
        state.ResumeTiming();
        
        g.fill_in(bj);
    }

    state.SetComplexityN(g.size() + g.edgeSize());
}

BENCHMARK(BM_fill_in)->RangeMultiplier(2)->Range(64, 8<<10)->Complexity();
BENCHMARK(BM_fill_in)->RangeMultiplier(2)->Range(64, 8<<10)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
