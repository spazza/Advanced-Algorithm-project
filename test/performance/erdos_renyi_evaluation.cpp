#include <benchmark/benchmark.h>
#include "Graph.hpp"

static void BM_erdos_renyi(benchmark::State& state) {
    CustomGraph::Graph g;
    
    for(auto _ : state) {
        state.PauseTiming();
        g.clear();
        state.ResumeTiming();
        g.generateRandomGraph(state.range(0));
    }
    
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_erdos_renyi)->RangeMultiplier(2)->Range(2,1024)->Complexity();

BENCHMARK_MAIN();