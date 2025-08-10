#include <cctype>
#include <cstring>
#include <iostream>
#include <benchmark/benchmark.h>

using namespace std;

__attribute__((always_inline))
inline char inline_funcall(char i) {
    return i + 32;
}

char funcall(char i) {
    return i + 32;
}

char tolower_with_lib_function_call() {
    char i = 'A';
    i = tolower(i);

    return i;
}

char tolower_with_function_call() {
    char i = 'A';
    i = funcall(i);

    return i;
}

char tolower_with_inline_function_call() {
    char i = 'A';
    i = inline_funcall(i);

    return i;
}

char tolower() {
    char i = 'A';
    i = i + 32;

    return i;
}

static void BM_TolowerWithLibFunctionCall(benchmark::State& state) {
    for (auto _ : state) {
        bool result = tolower_with_lib_function_call();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_TolowerWithLibFunctionCall)->Iterations(100000000);

static void BM_TolowerWithFunctionCall(benchmark::State& state) {
    for (auto _ : state) {
        bool result = tolower_with_function_call();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_TolowerWithFunctionCall)->Iterations(100000000);

static void BM_TolowerWithInlineFunctionCall(benchmark::State& state) {
    for (auto _ : state) {
        bool result = tolower_with_inline_function_call();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_TolowerWithInlineFunctionCall)->Iterations(100000000);

static void BM_TolowerWithoutFunctionCall(benchmark::State& state) {
    for (auto _ : state) {
        bool result = tolower();
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_TolowerWithoutFunctionCall)->Iterations(100000000);

BENCHMARK_MAIN();
