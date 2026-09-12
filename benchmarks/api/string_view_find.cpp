#include <benchmark/benchmark.h>
#include <string>
#include <string_view>
#include <zuu/string_view.hpp>

static const char* kTestData = "Hello World! This is a benchmark test string for zuu_string_view to measure search performance.";

static void BM_ZuuStrv_FindChr(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    char needle = 'e';
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find(needle));
    }
}

static void BM_StdStrv_FindChr(benchmark::State& state) {
    std::string_view sv(kTestData);
    char needle = 'e';
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find(needle));
    }
}

static void BM_ZuuStrv_FindStr(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    zuu::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find(needle));
    }
}

static void BM_StdStrv_FindStr(benchmark::State& state) {
    std::string_view sv(kTestData);
    std::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find(needle));
    }
}

static void BM_ZuuStrv_RFindChr(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    char needle = 'r';
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.rfind(needle));
    }
}

static void BM_StdStrv_RFindChr(benchmark::State& state) {
    std::string_view sv(kTestData);
    char needle = 'r';
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.rfind(needle));
    }
}

static void BM_ZuuStrv_RFindStr(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    zuu::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.rfind(needle));
    }
}

static void BM_StdStrv_RFindStr(benchmark::State& state) {
    std::string_view sv(kTestData);
    std::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.rfind(needle));
    }
}

static void BM_ZuuStrv_FindFirstOf(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    zuu::string_view needle("elo");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_first_of(needle));
    }
}

static void BM_StdStrv_FindFirstOf(benchmark::State& state) {
    std::string_view sv(kTestData);
    std::string_view needle("elo");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_first_of(needle));
    }
}

static void BM_ZuuStrv_FindLastOf(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    zuu::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_last_of(needle));
    }
}

static void BM_StdStrv_FindLastOf(benchmark::State& state) {
    std::string_view sv(kTestData);
    std::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_last_of(needle));
    }
}

static void BM_ZuuStrv_FindFirstNotOf(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    zuu::string_view needle("elo");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_first_not_of(needle));
    }
}

static void BM_StdStrv_FindFirstNotOf(benchmark::State& state) {
    std::string_view sv(kTestData);
    std::string_view needle("elo");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_first_not_of(needle));
    }
}

static void BM_ZuuStrv_FindLastNotOf(benchmark::State& state) {
    zuu::string_view sv(kTestData);
    zuu::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_last_not_of(needle));
    }
}

static void BM_StdStrv_FindLastNotOf(benchmark::State& state) {
    std::string_view sv(kTestData);
    std::string_view needle("zuu");
    for (auto _ : state) {
        benchmark::DoNotOptimize(sv);
        benchmark::DoNotOptimize(needle);
        benchmark::DoNotOptimize(sv.find_last_not_of(needle));
    }
}

BENCHMARK(BM_ZuuStrv_FindChr);
BENCHMARK(BM_StdStrv_FindChr);
BENCHMARK(BM_ZuuStrv_FindStr);
BENCHMARK(BM_StdStrv_FindStr);
BENCHMARK(BM_ZuuStrv_RFindChr);
BENCHMARK(BM_StdStrv_RFindChr);
BENCHMARK(BM_ZuuStrv_RFindStr);
BENCHMARK(BM_StdStrv_RFindStr);
BENCHMARK(BM_ZuuStrv_FindFirstOf);
BENCHMARK(BM_StdStrv_FindFirstOf);
BENCHMARK(BM_ZuuStrv_FindLastOf);
BENCHMARK(BM_StdStrv_FindLastOf);
BENCHMARK(BM_ZuuStrv_FindFirstNotOf);
BENCHMARK(BM_StdStrv_FindFirstNotOf);
BENCHMARK(BM_ZuuStrv_FindLastNotOf);
BENCHMARK(BM_StdStrv_FindLastNotOf);