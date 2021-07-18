#include <benchmark/benchmark.h>

static void BM_fill_in(benchmark::State& state) {
    for(auto _ : state) {
        
    }

}

BENCHMARK(BM_fill_in);

BENCHMARK_MAIN();