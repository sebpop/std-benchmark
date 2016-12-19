#include "benchmark/benchmark_api.h"
#include "test_configs.h"
#include "test_utils.h"

#include<algorithm>
#include<deque>
#include<list>
#include<map>
#include<set>
#include<vector>

template<typename V>
void BM_push_back(benchmark::State& state) {
  const unsigned N = state.range(0);
  V v;
  while (state.KeepRunning()) {
    for (unsigned i = 0; i < N; ++i)
      v.push_back(i);
  }
  state.SetComplexityN(N);
}

template<typename V>
void BM_push_back_resize(benchmark::State& state) {
  const unsigned N = state.range(0);
  V v(N);
  while (state.KeepRunning()) {
    for (unsigned i = 0; i < N; ++i)
      v.push_back(i);
  }
  state.SetComplexityN(N);
}

template<typename V>
void BM_push_back_vector_reserve(benchmark::State& state) {
  const unsigned N = state.range(0);
  V v;
  v.reserve(N);
  while (state.KeepRunning()) {
    for (unsigned i = 0; i < N; ++i)
      v.push_back(i);
  }
  state.SetComplexityN(N);
}

template<typename V>
void BM_insert(benchmark::State& state) {
  const unsigned N = state.range(0);
  V v(N, 1);
  auto val = *v.begin();
  while (state.KeepRunning()) {
    v.insert(v.begin(), val);
  }
  state.SetComplexityN(N);
}

template<typename V>
void BM_insert_last(benchmark::State& state) {
  const unsigned N = state.range(0);
  V v(N, 1);
  auto val = *v.begin();
  while (state.KeepRunning()) {
    v.insert(--v.end(), val);
  }
  state.SetComplexityN(N);
}

// Insert random elements
template<typename V>
void BM_assoc_insert_random(benchmark::State& state) {
  const unsigned N = state.range(0);
  using CVT = typename V::value_type;
  using VT = typename remove_const<CVT>::type;
  std::vector<VT> temp(N);
  fill_random(temp);
  V v;
  auto it = temp.begin();
  while (state.KeepRunning()) {
    v.insert(*it++);
    if (it == temp.end()) // FIXME: After temp.end insert will just return.
      it = temp.begin();
  }
  state.SetComplexityN(N);
}

// Insert random elements
template<typename V>
void BM_assoc_insert_seq(benchmark::State& state) {
  const unsigned N = state.range(0);
  using CVT = typename V::value_type;
  using VT = typename remove_const<CVT>::type;
  std::vector<VT> temp(N);
  fill_seq(temp);
  V v;
  auto it = temp.begin();
  while (state.KeepRunning()) {
    v.insert(*it++);
    if (it == temp.end()) // FIXME: After temp.end insert will just return.
      it = temp.begin();
  }
  state.SetComplexityN(N);
}

// Insert same element over and over.
template<typename V>
void BM_assoc_insert(benchmark::State& state) {
  const unsigned N = state.range(0);
  using CVT = typename V::value_type;
  using VT = typename remove_const<CVT>::type;
  VT temp = get_rand<VT>(N);
  V v;
  while (state.KeepRunning()) {
    v.insert(temp);
  }
  state.SetComplexityN(N);
}

/*/ Base case.
template <typename T>
void
check ()
{
}

template <typename T, typename container, typename... containers>
void
check ()
{
  COMPLEXITY_BENCHMARK_GEN(T, container, MSize);
  // Check rest of the properties.
  check<T, containers...>();
}

// All the sequence testing functors which take one argument.
#define CONTAINERS  std::vector<int>, std::list<int>

check<BM_push_back, CONTAINERS > ();*/


//std::forward_list<int> does not have push_back :(
static const int MSize = L2;
COMPLEXITY_BENCHMARK_GEN(BM_push_back, std::vector<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_push_back, std::list<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_push_back, std::deque<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_push_back_resize, std::vector<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_push_back_resize, std::list<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_push_back_resize, std::deque<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_push_back_vector_reserve, std::vector<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_insert, std::vector<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_insert, std::list<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_insert, std::deque<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_insert_last, std::vector<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_insert_last, std::list<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_insert_last, std::deque<int>, MSize);


COMPLEXITY_BENCHMARK_GEN(BM_assoc_insert, std::set<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_assoc_insert_random, std::set<int>, MSize);
COMPLEXITY_BENCHMARK_GEN(BM_assoc_insert_seq, std::set<int>, MSize);

COMPLEXITY_BENCHMARK_GEN(BM_assoc_insert, SINGLE_ARG(std::map<int, int>), MSize);
COMPLEXITY_BENCHMARK_GEN(BM_assoc_insert_random, SINGLE_ARG(std::map<int, int>), MSize);
COMPLEXITY_BENCHMARK_GEN(BM_assoc_insert_seq, SINGLE_ARG(std::map<int, int>), MSize);
BENCHMARK_MAIN()
