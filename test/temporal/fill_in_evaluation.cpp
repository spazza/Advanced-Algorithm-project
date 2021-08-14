#include <benchmark/benchmark.h>
#include "Graph.hpp"

// Performance evaluation of fill-in function
// This version does not produce meaningful results because I can't control the number of edges.

static void BM_fill_in_1(benchmark::State& state) {
    CustomGraph::Graph g;   
    for(auto _ : state) {
        // Graph creation discarded from the evaluation
        state.PauseTiming();
        g.clear();
        g.generateRandomGraph(state.range(0));

        vector<unsigned int> graphVerticesVector(g.size());
        for(auto v : g.getVertices())
            graphVerticesVector.push_back(v.first);

        BijectionFunction bj (graphVerticesVector);
        unsigned int prev_edges = g.edgeSize();
        state.ResumeTiming();
        
        // Evaluation of fill-in
        g.fill_in(bj);

        // The complexity is given by the sum between the number of vertices and the number of edges.
        state.PauseTiming();
        state.SetComplexityN(g.size() + prev_edges);
        state.ResumeTiming();
    }   
}

//BENCHMARK(BM_fill_in_1)->DenseRange(8, 96, 8)->Complexity();
//BENCHMARK(BM_fill_in_1)->DenseRange(8, 96, 8)->Complexity(benchmark::oN);

//BENCHMARK(BM_fill_in_1)->DenseRange(24, 56, 8)->Complexity();
//BENCHMARK(BM_fill_in_1)->DenseRange(24, 56, 8)->Complexity(benchmark::oN);

//BENCHMARK(BM_fill_in_1)->RangeMultiplier(2)->Range(128,1024)->Complexity();
//BENCHMARK(BM_fill_in_1)->RangeMultiplier(2)->Range(128,1024)->Complexity(benchmark::oN);


// Second version to evaluate the performance of fill-in function
// In that case I can control both numbers of vertices and edges.

static void BM_fill_in_2(benchmark::State& state) {
    CustomGraph::Graph g;   
    for(auto _ : state) {
        // Graph creation discarded from the evaluation
        state.PauseTiming();
        g.clear();
        g.generateRandomGraphPrecise(state.range(0));

        vector<unsigned int> graphVerticesVector(g.size());
        for(auto v : g.getVertices())
            graphVerticesVector.push_back(v.first);

        BijectionFunction bj (graphVerticesVector);
        state.ResumeTiming();
        
        // Evaluation of fill-in
        g.fill_in(bj);
    }   
    state.SetComplexityN(state.range(0));
}

//BENCHMARK(BM_fill_in_2)->DenseRange(128, 512, 64)->Complexity();
//BENCHMARK(BM_fill_in_2)->DenseRange(128, 512, 64)->Complexity(benchmark::oN);

//BENCHMARK(BM_fill_in_2)->RangeMultiplier(2)->Range(64, 8<<6)->Complexity();
//BENCHMARK(BM_fill_in_2)->RangeMultiplier(2)->Range(64, 8<<6)->Complexity(benchmark::oN);

// Third version to evaluate the performance of fill-in function.
// Now I set the complexity by adding the number of vertices and the new amount of edges.

static void BM_fill_in_3(benchmark::State& state) {
    CustomGraph::Graph g;   
    for(auto _ : state) {
        // Graph creation discarded from the evaluation
        state.PauseTiming();
        g.clear();
        g.generateRandomGraphPrecise(state.range(0));

        vector<unsigned int> graphVerticesVector(g.size());
        for(auto v : g.getVertices())
            graphVerticesVector.push_back(v.first);

        BijectionFunction bj (graphVerticesVector);
        state.ResumeTiming();
        
        // Evaluation of fill-in
        g.fill_in(bj);
        
        state.PauseTiming();
        state.SetComplexityN(g.size() + g.edgeSize());
        state.ResumeTiming();
    }   
}

BENCHMARK(BM_fill_in_3)->RangeMultiplier(2)->Range(8, 2<<8)->Complexity();
BENCHMARK(BM_fill_in_3)->RangeMultiplier(2)->Range(8, 2<<8)->Complexity(benchmark::oN);

BENCHMARK_MAIN();