#include <benchmark/benchmark.h>

#include <cstddef>
#include <string>
#include <string_view>

#include <zuu/string_view.hpp>

namespace {

enum class match_position : int {
  begin = 0,
  middle = 1,
  end = 2,
  miss = 3,
};

constexpr char kCharNeedle = 'z';
constexpr char kStringNeedle[] = "needle";
constexpr std::size_t kStringNeedleSize = sizeof(kStringNeedle) - 1;

const char* scenario_name(match_position scenario) {
  switch (scenario) {
  case match_position::begin:
    return "begin";
  case match_position::middle:
    return "middle";
  case match_position::end:
    return "end";
  case match_position::miss:
    return "miss";
  }
  return "unknown";
}

template <bool Reverse>
bool scans_entire_haystack(match_position scenario) {
  return scenario == match_position::miss ||
         (Reverse ? scenario == match_position::begin
                  : scenario == match_position::end);
}

std::string make_char_haystack(std::size_t size, match_position scenario) {
  std::string haystack(size, 'a');
  if (scenario == match_position::begin) {
    haystack.front() = kCharNeedle;
  } else if (scenario == match_position::middle) {
    haystack[size / 2] = kCharNeedle;
  } else if (scenario == match_position::end) {
    haystack.back() = kCharNeedle;
  }
  return haystack;
}

std::string make_string_haystack(std::size_t size, match_position scenario) {
  std::string haystack(size, 'a');
  if (scenario == match_position::begin) {
    haystack.replace(0, kStringNeedleSize, kStringNeedle);
  } else if (scenario == match_position::middle) {
    haystack.replace((size - kStringNeedleSize) / 2, kStringNeedleSize,
                     kStringNeedle);
  } else if (scenario == match_position::end) {
    haystack.replace(size - kStringNeedleSize, kStringNeedleSize,
                     kStringNeedle);
  }
  return haystack;
}

template <typename View, bool Reverse>
void benchmark_character_search(benchmark::State& state) {
  const std::size_t size = static_cast<std::size_t>(state.range(0));
  const match_position scenario =
      static_cast<match_position>(state.range(1));
  const std::string haystack = make_char_haystack(size, scenario);
  const View view(haystack.data(),
                  static_cast<typename View::size_type>(haystack.size()));

  state.SetLabel(scenario_name(scenario));
  for (auto _ : state) {
    benchmark::DoNotOptimize(view);
    benchmark::DoNotOptimize(kCharNeedle);
    if (Reverse) {
      benchmark::DoNotOptimize(view.rfind(kCharNeedle));
    } else {
      benchmark::DoNotOptimize(view.find(kCharNeedle));
    }
  }
  if (scans_entire_haystack<Reverse>(scenario)) {
    state.SetBytesProcessed(
        static_cast<int64_t>(state.iterations() * haystack.size()));
  }
}

template <typename View, bool Reverse>
void benchmark_string_search(benchmark::State& state) {
  const std::size_t size = static_cast<std::size_t>(state.range(0));
  const match_position scenario =
      static_cast<match_position>(state.range(1));
  const std::string haystack = make_string_haystack(size, scenario);
  const View view(haystack.data(),
                  static_cast<typename View::size_type>(haystack.size()));
  const View needle(kStringNeedle,
                    static_cast<typename View::size_type>(kStringNeedleSize));

  state.SetLabel(scenario_name(scenario));
  for (auto _ : state) {
    benchmark::DoNotOptimize(view);
    benchmark::DoNotOptimize(needle);
    if (Reverse) {
      benchmark::DoNotOptimize(view.rfind(needle));
    } else {
      benchmark::DoNotOptimize(view.find(needle));
    }
  }
  if (scans_entire_haystack<Reverse>(scenario)) {
    state.SetBytesProcessed(
        static_cast<int64_t>(state.iterations() * haystack.size()));
  }
}

static void BM_Zuu_FindChar_Scenarios(benchmark::State& state) {
  benchmark_character_search<zuu::string_view, false>(state);
}

static void BM_Std_FindChar_Scenarios(benchmark::State& state) {
  benchmark_character_search<std::string_view, false>(state);
}

static void BM_Zuu_RFindChar_Scenarios(benchmark::State& state) {
  benchmark_character_search<zuu::string_view, true>(state);
}

static void BM_Std_RFindChar_Scenarios(benchmark::State& state) {
  benchmark_character_search<std::string_view, true>(state);
}

static void BM_Zuu_FindString_Scenarios(benchmark::State& state) {
  benchmark_string_search<zuu::string_view, false>(state);
}

static void BM_Std_FindString_Scenarios(benchmark::State& state) {
  benchmark_string_search<std::string_view, false>(state);
}

static void BM_Zuu_RFindString_Scenarios(benchmark::State& state) {
  benchmark_string_search<zuu::string_view, true>(state);
}

static void BM_Std_RFindString_Scenarios(benchmark::State& state) {
  benchmark_string_search<std::string_view, true>(state);
}

#define REGISTER_SEARCH_SCENARIOS(function)                                      \
  BENCHMARK(function)->ArgsProduct({{8, 64, 256, 4096, 65536}, {0, 1, 2, 3}})

REGISTER_SEARCH_SCENARIOS(BM_Zuu_FindChar_Scenarios);
REGISTER_SEARCH_SCENARIOS(BM_Std_FindChar_Scenarios);
REGISTER_SEARCH_SCENARIOS(BM_Zuu_RFindChar_Scenarios);
REGISTER_SEARCH_SCENARIOS(BM_Std_RFindChar_Scenarios);
REGISTER_SEARCH_SCENARIOS(BM_Zuu_FindString_Scenarios);
REGISTER_SEARCH_SCENARIOS(BM_Std_FindString_Scenarios);
REGISTER_SEARCH_SCENARIOS(BM_Zuu_RFindString_Scenarios);
REGISTER_SEARCH_SCENARIOS(BM_Std_RFindString_Scenarios);

#undef REGISTER_SEARCH_SCENARIOS

} // namespace
