#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <vector>
#include <cmath>


#include <benchmark/benchmark.h>

template <typename T>
std::vector<T> GenerateData(int count) {
  std::vector<T> data;
  data.reserve(count);

  // Seed with a real random value, if available.
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, 10000);

  for (int i=0; i<count; ++i) {
    data.emplace_back(static_cast<T>(uniform_dist(e1)));
  }
  return data;
}

// For some reason this does not work:
// template <typename T>
// T VectorSum(const std::vector<T>& vals) __attribute__((noinline));

template <typename T>
T VectorSum(const std::vector<T>& vals) {
  T accum = 0;
  for(auto v : vals) {
    accum += v;
  }
  return accum;
}

template <typename T>
void BM_vectorSum(benchmark::State& state) {
  auto data = GenerateData<T>(state.range(0));
  for (auto _ : state) {
    // This code gets timed
    auto res = VectorSum<T>(data);
    benchmark::DoNotOptimize(res);
  }
  state.SetBytesProcessed(
      static_cast<int64_t>(state.iterations() * state.range(0) * sizeof(T)));
}

BENCHMARK_TEMPLATE(BM_vectorSum, double)->Range(65535, 65535);
BENCHMARK_TEMPLATE(BM_vectorSum, float)->Range(65535, 65535);
BENCHMARK_TEMPLATE(BM_vectorSum, int64_t)->Range(65535, 65535);
BENCHMARK_TEMPLATE(BM_vectorSum, int8_t)->Range(65535, 65535);
